#include "ocpch.h"
#include "ComponentPack.h"

namespace oc {

	template<typename T>
	T& ComponentPack<T>::Create(Entity entity)
	{
		// Invalid entry is not allowed
		OC_ASSERT(entity != INVALID_ENTITY, "Invalid entry is not allowed!");

		// Only one of  this component type per entity is allowed
		OC_ASSERT(!Contains(entity), "Component already exists for this entity!");

		// Check entity count
		OC_ASSERT(entities.size() == components.size(), "Entities and components do not match!");
		OC_ASSERT(lookup.size() == components.size(), "Entities and components do not match!");

		// Update entity lookup table
		lookup[entity] = components.size();

		// Push new components to end
		components.push_back(entity);

		// Push corresponding entity
		entities.push_back(entity);

		return components.back();
	}

	template<typename T>
	bool ComponentPack<T>::Contains(Entity entity) const
	{
		return lookup.find(entity) != lookup.end();
	}

	template<typename T>
	T* ComponentPack<T>::GetComponent(Entity entity)
	{
		auto it = lookup.find(entity);
		OC_ASSERT(it != lookup.end(), "Entity {} does not exist in this component manager!", entity);
		if (it != lookup.end()) {
			return &components[it->second];
		}
		else return nullptr;
	}


	template<typename T>
	void ComponentPack<T>::Remove(Entity entity)
	{
		auto it = lookup.find(entity);
		OC_ASSERT(it != lookup.end(), "Entity {} trying to be removed does not exist!", entity);
		if (it != lookup.end()) {

			const size_t index = it->second;
			const Entity entity = entities[index];

			if (index < components.size() - 1)
			{
				// Swap dead element with last one
				components[index] = std::move(components.back());
				entities[index] = entities.back();

				lookup[entities[index]] = index;
			}

			// Shrink the container
			components.pop_back();
			entities.pop_back();
			lookup.erase(entity);
		}
	}




}