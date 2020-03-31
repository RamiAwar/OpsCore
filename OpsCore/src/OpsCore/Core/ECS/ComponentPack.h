#pragma once

#include "Core.h"
#include "Log.h"
#include "Entity.h"

#include <vector>
#include <unordered_map>


namespace oc {


	class IComponentPack
	{
	public:
		virtual ~IComponentPack() = default;
	};

	template<typename T>
	class ComponentPack : public IComponentPack {

	public:

		/**
		* Creates a component of type <T>, bind the entity to it, and return a reference to the component.
		**/
		T& Create(Entity entity);

		/**
		* Checks whether or not an entity is bound to a component of this type
		**/
		bool Contains(Entity entity) const;

		/**
		* Returns the number of components of type <T> in this component manager
		**/
		inline size_t GetCount() const { return components.size(); }

		/**
		* Indexing operator overload returns the component at index specified
		**/
		T& operator[](size_t index) { return components[index]; }


		/**
		* Returns the entity associated with component at the index specified
		**/
		Entity GetEntity(size_t index) const { return entities[index]; }


		/**
		* Returns the component bound to this entity (ex fetch one component from another component in an entity)
		**/
		T* GetComponent(Entity entity);

		
		/**
		* Detaches component from entity specified and deletes it
		* Deletion happens by moving back of the array into element to be deleted O(1)
		* TODO: Problematic when relying on component ordering, try to find a fix
		**/
		void Remove(Entity entity);


	private:
		std::vector<T> components;
		std::vector<Entity> entities;
		std::unordered_map<Entity, size_t> lookup;
	};


}