#pragma once

#include "OpsCore/Core/VVector.h"
#include "Entity.h"
#include "Archetype.h"
#include <unordered_map>
#include <unordered_set>

#define MB 1000000

namespace oc::ECS {

	struct Record {
		Archetype* archetype;
		int index;
	};

	class World {

	public:

		World();

		/**
		*	Creates an entity and returns it (an id and generation)
		*	Do not want to return by reference so that entity holder can check if it was destroyed by comparing generation
		**/
		Entity CreateEntity();
		/**
		*	Destroys an entity by marking it for reuse, using the free-list structure.
		**/
		void DestroyEntity(Entity entity);
		/**
		*	Checks if the entity is alive by comparing the give entity's generation to the stored entity's generation
		**/
		inline bool IsAlive(Entity entity);

		/**
		*	Function for generating an archetype signature
		**/
		template<typename ...Component>
		static Signature GenerateSignature() {

			const std::size_t n_components = sizeof...(Component);
			// Check that number of components less than MAX_COMPONENTS
			OC_ASSERT(n_components < MAX_COMPONENTS, "Number of components is above permitted number");

			const char* component_types[] = { typeid(Component).name()... };

			Signature signature;

			signature.size = n_components;

			std::unordered_set<uint64_t> check_unique;
			for (int i = 0; i < n_components; i++) {
				signature.component_hashes[i] = hash_fnv1a(component_types[i]);
				check_unique.insert(signature.component_hashes[i]);
				signature.hash ^= signature.component_hashes[i];
			}

			if (check_unique.size() != n_components) {
				throw std::invalid_argument("Component type hash collision: Duplicate Components suspected. Check that each is unique!");
			}

			return signature;
		}

		
		template<typename T>
		inline void AddComponent(Entity entity, T& component) {
			
		}

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
		*	Getter functions for testing
		**/
		inline const Entity		_GetEntity(int id) { return entities[id]; }
		inline const size_t		_GetEntitySize() { return entities.size(); }
		inline const uint32_t	_GetNextAvailable() { return next_available; }


	private:
		oc::VVector<Entity> entities;
		oc::VVector<Archetype> archetypes;

		//std::unordered_map<Entity, Record> entity_index;

		uint32_t next_available;

	};

}