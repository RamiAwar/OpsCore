#pragma once
#include "OpsCore/Core/VVector.h"
#include <vector>
#include <array>
#include "Metatype.h"
#include "ComponentArray.h"

#define MAX_COMPONENTS 32


namespace oc::ECS {


	/**
	*	An archetype houses all entities that have the same set of components
	*	A key idea in designing this struct is keeping it lightweight. All functionality
	*	is moved to the World class which manages Archetypes. 
	**/
	struct Archetype {

		uint64_t signature;

		// TODO: change to VVector
		std::vector<ComponentArray*> components; // Vertical list of component types

	};






	//struct ArchetypeNode; // forward declaration

	//struct ArchetypeEdge {
	//	ArchetypeNode* node;
	//	uint64_t component_hash;
	//};

	//struct ArchetypeNode {
	//	Archetype* archetype;
	//	std::vector<ArchetypeEdge> addition;
	//	std::vector<ArchetypeEdge> removal;
	//};

}