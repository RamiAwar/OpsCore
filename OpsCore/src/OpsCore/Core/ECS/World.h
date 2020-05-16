#pragma once

#include "OpsCore/Core/VVector.h"

#include "EntityManager.h"
#include "Archetype.h"
#include <unordered_map>
#include <unordered_set>

#define MB 1000000

#define MAX_ARCHETYPES 20000

namespace oc::ECS {

	struct Record {
		Archetype* node;
		int index;
	};

	class World {

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
		Entity CreateEntity() {

			// Create empty entity
			Entity entity = entityManager->CreateEntity();
			Archetype* archetype = nullptr;

			if constexpr (sizeof...(Components) != 0) {

				// Create metatype list (hash of each component + their sizes)
				const Metatype* types[] = { Metatype::BuildMetatype<Components>()... };
				constexpr size_t n_types = (sizeof(types) / sizeof(*types));
				// Sort metatypes
				sort_metatypes(types, n_types);
				
				// Find or create archetype with signature x
				uint64_t signature = hash_fnv1a(types, n_types);
				//std::cout << signature << std::endl;
			
				auto iter = signature_archetype_map.find(signature);
				if (iter != signature_archetype_map.end()) {
					// If archetype found
					archetype = iter->second;
				}
				else {
					// Create archetype
					/*Archetype arch = { signature, std::vector<ComponentArray*>(n_types) };
					for (int i = 0; i < n_types; i++) {
						void* buffer = malloc(types[i]->size * MAX_ENTITIES);
					}*/
				}

			} else {
				archetype = empty_archetype;
			}

			//return BindEntityArchetype(entity, archetype);
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

		template<typename T>
		inline void AddComponent(Entity entity, T component);

	/*	template<typename T>
		bool HasComponent(Entity entity) {
			
			Record& record = entity_index[entity];
			Archetype* archetype = record.archetype;

			for (int i = 0; i < archetype->signature.size; i++) {
				if (hash_fnv1a(typeid(T).name()) == archetype->signature.component_hashes[i]) {
					return static_cast<T*>(archetype->components[i].elements[record.index * (int)archetype->components[i].elements.size]);
				}
			}

		}*/


		/**
		*	Returns a pointer to the specified component.
		*	Loops over all components in a certain archetype until the specific type is found, and then returns the index
		*	that is stored in the record pertaining to this entity specifically.
		**/
		template<typename T>
		T* GetComponent(Entity entity) {
			
			// Check that entity is still alive
			if (!isAlive(entity)) {
				throw std::exception("Attempting to add component to an entity that was destroyed.");
			}
			
			Record* record = archetype_index[entity.id];
			uint32_t hash = GenerateComponentHash<T>();

			// Find the component index (fine to loop only 32 components)
			for (int i = 0; i < record.node->archetype->signature.size; i++) {
				if (hash == record->node->archetype->signature.component_hashes[i]) {
					return static_cast<T*>(record->node->archetype->components[i].elements[record->index]);
				}
			}
			
			throw std::exception("Component does not exist!");
		}



		/**
		*	Getter functions for testing ONLY
		**/
		inline const Entity		_GetEntity(int id) { return entityManager->_GetEntity(id); }
		inline const size_t		_GetEntitySize() { return entityManager->_GetEntitySize(); }
		inline const uint32_t	_GetNextAvailable() { return entityManager->_GetNextAvailable(); }


		/**
		*	Function for generating an archetype signature
		**/
		//template<typename ...Component>
		//static Signature GenerateSignature() {

		//	const std::size_t n_components = sizeof...(Component);
		//	// Check that number of components less than MAX_COMPONENTS
		//	OC_ASSERT(n_components < MAX_COMPONENTS, "Number of components is above permitted number");

		//	const char* component_types[] = { typeid(Component).name()... };

		//	Signature signature = { {0}, 0, 0 };

		//	signature.size = n_components;

		//	std::unordered_set<uint64_t> check_unique;
		//	for (int i = 0; i < n_components; i++) {
		//		signature.component_hashes[i] = hash_fnv1a(component_types[i]);
		//		check_unique.insert(signature.component_hashes[i]);
		//		signature.hash ^= signature.component_hashes[i];
		//	}

		//	if (check_unique.size() != n_components) {
		//		throw std::invalid_argument("Component type hash collision: Duplicate Components suspected. Check that each is unique!");
		//	}

		//	return signature;
		//}

		/*template<typename Component>
		static uint64_t GenerateComponentHash() {
			const char* component_type = typeid(Component).name();
			return hash_fnv1a(component_type);
		}*/


		//ArchetypeNode* root_archetype_node;

	private:

		EntityManager* entityManager;
		
		/**
		*	A map from entity IDs to Archetype pointers. This will quickly get which archetype an entity belongs to.
		**/
		std::unordered_map<uint32_t, Record> entity_archetype_map;

		/**
		*	A map from archetype signatures to archetype pointers so we can fetch an archetype from the hash of its components
		**/
		std::unordered_map<uint64_t, Archetype*> signature_archetype_map;

		Archetype* empty_archetype;
	}; 

}