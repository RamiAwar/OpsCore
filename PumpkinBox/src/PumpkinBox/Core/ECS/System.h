#pragma once

#include "Entity.h"
#include "Archetype.h"




namespace pb::ECS {
	
	// Forward declaration of world to hold reference to static instance upon its creation
	class World;

	/**
	*	A Group is a list of references to archetypes and a signature.
	*	archetypes: List of pointers to archetypes
	*	signature: List of component hashes (uint64_t) to match with archetypes
	**/
	struct Group {
		std::vector<Archetype*> archetypes;
		std::vector<uint64_t> signature;
	};

	template<typename T>
	struct ComponentIterator {
		
		ComponentIterator(Group* _group) : group(_group){}

		T* operator[](size_t index) {

			// Update max length
			_size = 0;
			for (int i = 0; i < group->archetypes.size(); i++) {
				_size += group->archetypes[i]->components.size();
			}
			
			// Which archetype are we at? Need to check sizes vs index
			size_t current_index = index;
			size_t archetype_index = 0;
			for (int i = 0; i < group->archetypes.size(); i++) {
				archetype_index = i;
				if (current_index < group->archetypes[i].size()) {
					break;
				}
				else {
					current_index -= group->archetypes[i].size()-1;
				}
			}

			// Current index should be the right index into the right archetype
			// Find the right row
			size_t current_row = 0;
			uint64_t hash = typeid(T).hash_code();
			for (int i = 0; i < group->archetypes[archetype_index]->n_types; i++) {
				if (hash == group->archetypes[archetype_index]->types[i]->hash) {
					current_row = i;
				}
			}

			// Fetch the demanded element from right index (current_index)
			return (T*)(group->archetypes[archetype_index]->components[current_row][current_index]);
		}	

		size_t size() {
			return _size;
		}

	private:
		Group* group;
		size_t _size;
	};

	class System {
	
	public:

		System();

		virtual void Update(float delta)=0;
		
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