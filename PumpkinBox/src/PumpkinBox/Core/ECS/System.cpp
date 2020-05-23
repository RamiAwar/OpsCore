#include "pbpch.h"
#include "System.h"

namespace pb::ECS {

	std::vector<System*> System::instance_list;
	World* System::world;

	System::System(){}

	void System::SetWorld(World* _world) {
		if (world == nullptr) {
			world = _world;
		}
	}




}