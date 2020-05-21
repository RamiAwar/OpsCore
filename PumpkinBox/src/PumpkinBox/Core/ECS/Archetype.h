#pragma once
#include "PumpkinBox/Core/VVector.h"
#include <vector>
#include <array>
#include "Metatype.h"
#include "ComponentArray.h"

#define MAX_COMPONENTS 32


namespace pb::ECS {

	/**
	*	An archetype houses all entities that have the same set of components
	*	A key idea in designing this struct is keeping it lightweight. All functionality
	*	is moved to the World class which manages Archetypes. 
	**/
	struct Archetype {

		uint64_t signature;
		const Metatype** types;
		size_t n_types;

		// TODO: change to VVector
		std::vector<ComponentArray> components; // Vertical list of component types

	};


	/**
	*	Structure to link entity to an archetype.
	*	archetype: Pointer to the archetype the entity's components are stored in
	*	component_index: Index of the entity's components in each component array inside the archetype
	**/
	struct Record {
		Archetype* archetype;
		int component_index;
	};





}