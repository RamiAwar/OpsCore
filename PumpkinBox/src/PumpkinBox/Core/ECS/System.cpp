#include "pbpch.h"
#include "System.h"

namespace pb::ECS {

	std::vector<System*> System::instance_list;
	World* System::world;

	System::System(){
		// Add itself automatically to static list
		System::instance_list.push_back(this);
		std::cout << "Hello from system" << std::endl;
	}

	void System::SetWorld(World* _world) {
		if (world == nullptr) {
			world = _world;
		}
	}




}