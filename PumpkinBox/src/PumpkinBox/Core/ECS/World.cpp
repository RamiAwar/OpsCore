#include "pbpch.h"
#include "World.h"
#include "EntityManager.h"
#include "Archetype.h"

namespace pb::ECS {

	World::World()
		: archetypes(pb::VVector<Archetype>(1000*MB))
	{
		// Create empty archetype
		this->entityManager = new EntityManager();
		this->archetypes.push_back(Archetype({ 0, {} }));
	}

	void World::DestroyEntity(Entity entity) {
		entityManager->DestroyEntity(entity);
	}

	inline bool World::IsAlive(Entity entity) {
		return entityManager->IsAlive(entity);
	}

	void World::_FindOrCreateArchetype(const Entity& entity, const Metatype** types, size_t n_types) {

		uint64_t signature = hash_fnv1a(types, n_types);
		Archetype* archetype = nullptr;
		Record record;

		auto iter = signature_archetype_map.find(signature);
		if (iter != signature_archetype_map.end()) {
			// If archetype found
			archetype = iter->second;
			// Add default components
			int entity_index = archetype->components[0]._size();
			for (int i = 0; i < n_types; i++) {
				void* component = archetype->components[i].create_empty_slot();
				types[i]->constructor(component);
			}
			// Create and add record
			record.archetype = archetype;
			record.component_index = entity_index;
			entity_archetype_map[entity.index] = record;
		}
		else {
			// Create archetype
			Archetype arch;
			arch.signature = signature;
			arch.n_types = n_types;
			arch.types = (const Metatype**)malloc(n_types * sizeof(Metatype*));

			// For each type, save it in archetype types, construct default component and push to component array
			for (int i = 0; i < n_types; i++) {

				arch.types[i] = types[i];

				ComponentArray arr(types[i]->size);

				void* component = arr.create_empty_slot();
				types[i]->constructor(component);

				arch.components.push_back(std::move(arr));
			}
			// Add archetype to archetypes array
			archetypes.push_back(std::move(arch));
			signature_archetype_map[signature] = &archetypes[archetypes.size() - 1];
			record.archetype = &archetypes[archetypes.size() - 1];
			record.component_index = 0;
			entity_archetype_map[entity.index] = record;
		}

	
	}

}
