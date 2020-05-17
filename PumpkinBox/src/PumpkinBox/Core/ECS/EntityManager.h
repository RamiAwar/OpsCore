#pragma once

#pragma once

#include "PumpkinBox/Core/VVector.h"
#include "Entity.h"

#include <unordered_map>
#include <unordered_set>

#define MB 1000000

#define MAX_ENTITIES 500000

namespace pb::ECS {

	class EntityManager {

	public:

		/**
		*	Constructor initializes virtual memory and the freelist structure for the entities array and archetypes array (no free list here)
		*	Then creates an empty Archetype node to act as the root node in the Archetype graph. The archetype graph allows for quick
		*	addition and removal of components.
		**/
		EntityManager();

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
		inline bool IsAlive(Entity entity) {
			return entity.generation == entities[entity.index].generation;
		}

		/**
		*	Getter functions for testing
		**/
		inline const Entity		_GetEntity(int id) { return entities[id]; }
		inline const size_t		_GetEntitySize() { return entities.size(); }
		inline const uint32_t	_GetNextAvailable() { return next_available; }


	private:
		pb::VVector<Entity> entities;
		uint32_t next_available;

	};

}