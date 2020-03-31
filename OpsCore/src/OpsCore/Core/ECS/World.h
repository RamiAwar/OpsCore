#pragma once

#include "OpsCore/Core/VVector.h"
#include "Entity.h"

#define MB 1000000

namespace oc::ECS {


	class World {

	public:

		World()
			: entities(oc::VVector<Entity>(sizeof(Entity)*MB)),
			next_available(0)
		{
		}

		/**
		*	Creates an entity and returns it (an id and generation)
		*	Do not want to return by reference so that entity holder can check if it was destroyed by comparing generation
		**/
		Entity CreateEntity() {

			if (next_available == entities.size()) {

				// Create new generation 0 entity
				Entity entity;
				entity.index = next_available;
				entity.generation = 0;

				entities.push_back(entity);
				next_available++;

				return entity;
			}
			else {
				Entity entity;
				entity.index = next_available; // because it doesn't have an index due to union (deleted element to be reused)
				entity.generation = entities[next_available].generation; // generation is outside of union so is available
				next_available = entities[next_available].next; // set next available to the next reusable element

				return entity;
			}
		}

		void DestroyEntity(Entity entity) {
			uint32_t index = entity.index;
			entities[index].next = next_available;
			entities[index].generation++;
			next_available = index;
		}

		oc::VVector<Entity> entities;
		uint32_t next_available;

	private:



		
	};

}