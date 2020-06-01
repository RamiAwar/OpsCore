#pragma once



#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include <ostream>

#include "PumpkinBox/Core/VVector.h"
#include "PumpkinBox/Utils/Typename.h"

#include "EntityManager.h"
#include "Archetype.h"
#include "System.h"


#define MB 1000000

#define MAX_ARCHETYPES 20000

namespace pb::ECS 
{
	class World 
	{
	public:	
		/**
		*	Constructor initializes virtual memory and the freelist structure for the entities array and archetypes array (no free list here)
		*	Then creates an empty Archetype node to act as the root node in the Archetype graph. The archetype graph allows for quick 
		*	addition and removal of components.
		**/
		World();

		/**
		*	Creates an entity and returns it (an id and generation)
		*	Do not want to return by reference so that entity holder can check if it was destroyed by comparing generation
		**/
		template<typename ...Components>
		Entity CreateEntity(const char* name="") {

			// Create empty entity
			Entity entity = entityManager->CreateEntity();
			if(name != "") entity_names[entity.index] = std::string(name);

			if constexpr (sizeof...(Components) != 0) {

				// Create metatype list (hash of each component + their sizes)
				const Metatype* types[] = { Metatype::BuildMetatype<Components>()... };
				static_string names[] = { type_name<Components>()... };
				constexpr size_t n_types = (sizeof(types) / sizeof(*types));
				
				for (int i = 0; i < n_types; i++) {
					std::stringstream stream;
					stream << names[i];
					std::string str = stream.str();
					
					uint64_t hash = types[i]->hash;
					component_names[hash] = str;
				}

				// Sort metatypes
				sort_metatypes(types, n_types);
				
				// Find or create archetype with signature x
				_FindOrCreateArchetype(entity, types, n_types);

			} else {

				// No components specifies, just assign to empty archetype
				Record record;
				record.archetype = &archetypes[0];
				record.component_index = 0;
				entity_archetype_map[entity.index] = record;

			}
			// Return created entity **COPY**, so we can check generation for changes
			return entity;
		}

		/**
		*	Destroys an entity by marking it for reuse, using the free-list structure.
		**/
		void DestroyEntity(Entity entity);
		/**
		*	Checks if the entity is alive by comparing the give entity's generation to the stored entity's generation
		**/
		inline bool IsAlive(Entity entity);


		/**
		*	Adds a component to an entity, moving it from its current archetype to the new archetype
		**/
		//template<typename T>
		//inline void AddComponent(Entity entity, T component);


		/**
		*	Returns a boolean representing whether or not an entity has a certain component
		**/
		template<typename T>
		bool HasComponent(Entity entity) {
			
			// Check that entity is still alive
			if (!entityManager->IsAlive(entity)) {
				throw std::exception("Attempting to add component to an entity that was destroyed.");
			}

			const Record& record = entity_archetype_map[entity.index];
			uint64_t hash = typeid(T).hash_code();

			// Find the component index (fine to loop only 32 components)
			for (int i = 0; i < record.archetype->n_types; i++) {
				if (hash == record.archetype->types[i]->hash) {
					// Component found, return it
					return true;
				}
			}
			
			return false;
		}


		/**
		*	Returns a pointer to the specified component.
		*	Loops over all components in a certain archetype until the specific type is found, and then returns the index
		*	that is stored in the record pertaining to this entity specifically.
		**/
		template<typename T>
		T* GetComponent(Entity entity) {
			
			// Check that entity is still alive
			if (!entityManager->IsAlive(entity)) {
				throw std::exception("Attempting to add component to an entity that was destroyed.");
			}
			
			const Record& record = entity_archetype_map[entity.index];
			uint64_t hash = typeid(T).hash_code();

			// Find the component index 
			for (int i = 0; i < record.archetype->n_types; i++) {
				if (hash == record.archetype->types[i]->hash) {
					// Component found, return it
					return (T*)(record.archetype->components[i][record.component_index]);
				}
			}
			
			throw std::exception("Error: Component does not exist!");
		}

		std::vector<std::string> GetComponentNamesList(Entity entity) {
			// Check that entity is still alive
			if (!entityManager->IsAlive(entity)) {
				throw std::exception("Attempting to add component to an entity that was destroyed.");
			}

			const Record& record = entity_archetype_map[entity.index];

			std::vector<std::string> out;

			// Find the component index 
			for (int i = 0; i < record.archetype->n_types; i++) {
				out.push_back(component_names[record.archetype->types[i]->hash]);
			}

			return out;
		}

		pb::VVector<Entity>* GetEntities() {
			return entityManager->GetEntities();
		}

		/**
		*	Returns a pointer to the specified component.
		*	Loops over all components in a certain archetype until the specific type is found, and then returns the index
		*	that is stored in the record pertaining to this entity specifically.
		**/
		template<typename T>
		void SetComponent(Entity entity, T& component) {

			// Check that entity is still alive
			if (!entityManager->IsAlive(entity)) {
				throw std::exception("Attempting to add component to an entity that was destroyed.");
			}

			const Record& record = entity_archetype_map[entity.index];
			uint64_t hash = typeid(T).hash_code();

			// Find the component index (fine to loop only 32 components)
			for (int i = 0; i < record.archetype->n_types; i++) {
				if (hash == record.archetype->types[i]->hash) {
					// Component found, return it
					memcpy((record.archetype->components[i][record.component_index]), &component, sizeof(T));
					return;
				}
			}

			throw std::exception("Error: Component does not exist!");
		}

		void _FindOrCreateArchetype(const Entity &entity, const Metatype** types, size_t n_types);


		template<typename ...Components>
		void RegisterSystem(System* system){

			if constexpr (sizeof...(Components) != 0) {

				// Create metatype list (hash of each component + their sizes)
				const Metatype* types[] = { Metatype::BuildMetatype<Components>()... };
				constexpr size_t n_types = (sizeof(types) / sizeof(*types));

				std::vector<size_t> user_defined_indices(n_types);
				std::iota(user_defined_indices.begin(), user_defined_indices.end(), 0);
				std::sort(user_defined_indices.begin(), user_defined_indices.end(), [&](size_t i, size_t j) {return types[i] < types[j]; });

				for (int i = 0; i < n_types; i++) {
					std::cout << user_defined_indices[i] << std::endl;
				}

				system->group.user_defined_indices = user_defined_indices;

				// Sort metatypes
				sort_metatypes(types, n_types);

				// Populate system group signature
				for (int i = 0; i < n_types; i++) {
					system->group.signature.push_back(types[i]->hash);
				}
				
				// Link system group with archetypes
				LinkSystem(system);

				systems.push_back(system);

			}
			else {

				// Issue error, as system has to have at least one component
				PB_ERROR("ECS Error: System registration has to include at least one component!");
			}
		}

		void LinkSystem(System* system);

		void Update(pb::Timestep ts) {
			for (System* system : systems) 
			{
				system->Update(ts);
			}
		}

		/**
		*	Helper function to check if archetype signature belongs in group. If it does,
		*	a pointer to the archetype is added to the group.
		**/
		void MatchArchetype(Archetype* archetype, Group* current_group);


		/**
		*	Testing functions
		**/
		inline const Entity		_GetEntity(int id) { return entityManager->_GetEntity(id); }
		inline const size_t		_GetEntitySize() { return entityManager->_GetEntitySize(); }
		inline const uint32_t	_GetNextAvailable() { return entityManager->_GetNextAvailable(); }



	private:

		/**
		* Instance of entity manager to manage all entities (remove, add, checkalive)
		**/
		EntityManager* entityManager;
		
		/**
		*	A map from entity IDs to Records, which contain archetype pointers and an index. This will quickly get which archetype an entity belongs to.
		**/
		std::unordered_map<uint32_t, Record> entity_archetype_map;

		/**
		*	A map from archetype signatures to archetype pointers so we can fetch an archetype from the hash of its components
		**/
		std::unordered_map<uint64_t, Archetype*> signature_archetype_map;

		/**
		*	Virtual memory vector for storing all archetypes and their components.
		**/
		pb::VVector<Archetype> archetypes;

		std::vector<System*> systems;

	public:
		std::unordered_map<uint64_t, std::string> component_names;
		std::unordered_map<uint32_t, std::string> entity_names;

	}; 

}