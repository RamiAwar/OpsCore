#pragma once

#include "Entity.h"
#include "Archetype.h"
#include "PumpkinBox/Core/Timestep.h"



namespace pb::ECS {
	
	// Forward declaration of world to hold reference to static instance upon its creation
	class World;

	/**
	*	A matched archetype is used to prematch archetype component array indices with the system's components.
	*	This allows for quicker fetching of the component arrays of a certain component (which would
	*	have needed a loop and manual checking each if its the right one). This was suggested by the 
	*	author of flecs (Sanders).
	**/
	struct MatchedArchetype {
		Archetype* archetype;
		std::vector<size_t> component_array_indices;
	};

	/**
	*	A Group is a list of references to archetypes and a signature.
	*	archetypes: List of pointers to archetypes
	*	signature: List of component hashes (uint64_t) to match with archetypes
	**/
	struct Group {
		std::vector<MatchedArchetype> matched_archetypes;
		std::vector<uint64_t> signature;
		std::vector<size_t> user_defined_indices;
	};

	template<typename T>
	struct ComponentIterator {
		
		ComponentIterator(Group* _group, size_t _component_index) : group(_group), component_index(_component_index){}

		T* operator[](size_t index) {
			
			if (index > _size) {
				throw std::out_of_range("Component index out of range");
			}
				
			// Which archetype are we at? Need to check sizes vs index
			size_t current_index = index;
			size_t archetype_index = 0;
			for (int i = 0; i < group->matched_archetypes.size(); i++) {
				archetype_index = i;
				if (current_index < group->matched_archetypes[i].archetype->components[0]._size()) {
					break;
				}
				else {
					current_index -= group->matched_archetypes[i].archetype->components[0]._size();
				}
			}

			// Current index should be the right index into the right archetype
			// Get the right row
			for (int i = 0; i < group->user_defined_indices.size(); i++) {
				if (component_index == group->user_defined_indices[i]) {
					component_index = i;
					break;
				}
			}

			size_t current_row = group->matched_archetypes[archetype_index].component_array_indices[component_index];

			// Fetch the demanded element from right index (current_index)
			return (T*)(group->matched_archetypes[archetype_index].archetype->components[current_row][current_index]);
	}	

		size_t size() {
			// Update max length
			_size = 0;
			for (int i = 0; i < group->matched_archetypes.size(); i++) {
				_size += group->matched_archetypes[i].archetype->components[0]._size();
			}
			return _size;
		}

	private:
		Group* group;
		size_t component_index;
		size_t _size;
	};

	class System {
	
	public:

		System();

		virtual void Update(pb::Timestep ts)=0;
		
		void SetWorld(World* _world);



	public:
		// Group that characterizes this system
		Group group;

		static std::vector<System*> instance_list;

	
	private:

		// Reference to world instnace
		static World* world;

		
	
	};

}