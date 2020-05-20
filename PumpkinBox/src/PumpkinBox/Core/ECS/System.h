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

	class System {
	
	public:

		System();

		virtual void Update(float delta)=0;
		
		template<typename ...Components>
		virtual void SetComponents() = 0;
		
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