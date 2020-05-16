#include "ocpch.h"
#include "World.h"
#include "EntityManager.h"
#include "Archetype.h"

namespace oc::ECS {

	World::World()
		/*: archetypes(oc::VVector<Archetype>(sizeof(Archetype)* MAX_ARCHETYPES))*/
	{
		// Create empty archetype
		this->entityManager = new EntityManager();
		this->empty_archetype = new Archetype({ 0, {} });


		//this->archetypes = oc::VVector<Archetype>(MAX_ARCHETYPES * sizeof(Archetype));

		//Signature empty_signature = { {0}, 0, 0 }; // Empty archetype signature
		//Archetype empty_archetype = { empty_signature, {} };
		//archetypes.push_back(empty_archetype);

		//root_archetype_node = new ArchetypeNode({ &archetypes[0], {}, {} });


	}

	

	void World::DestroyEntity(Entity entity) {
		entityManager->DestroyEntity(entity);
	}

	inline bool World::IsAlive(Entity entity) {
		return entityManager->IsAlive(entity);
	}

	template<typename T>
	inline void World::AddComponent(Entity entity, T component) {

		// Check that entity is still alive
		if (!entityManager->isAlive(entity)) {
			throw std::exception("Attempting to add component to an entity that was destroyed.");
		}

		// Find the archetype that this entity is attached to
		Record record = archetype_index[entity.index];

		// Find destination archetype
		// Loop over all addition edges
		uint32_t hash = GenerateComponentHash<T>();
		bool found_archetype = false;

		for (int i = 0; i < record.node->addition.size(); i++) {

			// If found destination archetype
			if (record.node->addition[i].component_hash == hash) {

				found_archetype = true;
				// Fetch archetype node
				ArchetypeNode* target_node = record.node->addition[i].node;

				// Copy current components to target archetype
				// Loop over current components to copy each to its correct position
				// TODO: TEST SPEED AGAINST USING MAP TO SPEED TO O(n)
				int new_component_index_in_target = 0;

				for (int j = 0; j < record.node->archetype->signature.size; j++) {
					for (int k = 0; k < target_node->archetype->signature.size; k++) {

						if (hash == target_node->archetype->signature.component_hashes[k]) {
							new_component_index_in_target = k;
						}

						if (record.node->archetype->signature.component_hashes[j] == target_node->archetype->signature.component_hashes[k]) {

							// We found corresponding index of component in target node
							// Copy source into target_node->archetype->components[k]
							//NO : THIS COPIES THE WHOLE COMPONENT ARRAY POINTER! //std::memcpy(target_node->archetype->components[k].elements, record.node->archetype->components[j].elements, record.node->archetype->components[j].element_size);
							//record.node->archetype->components.erase(j);
							
							
							
							j--; // so we revisit node since all elements will be pushed back by one
							break;
						}
					}
				}

				// Copy end component into right place
				static_cast<oc::VVector<T>*>(target_node->archetype->components[new_component_index_in_target].elements)->push_back(component);
				break;

			}
		}

		// If archetype not found, create archetype
		if (!found_archetype) {

		}

		// Copy components from source to destination


		// Remove entity from that archetype
		// WARNING: Very costly operation.
		// TODO: Find a way to optimize this
		//record.node->archetype->components.erase(record.index);
	
		// TODO: Remember to save the component index in the record!
	}


}
