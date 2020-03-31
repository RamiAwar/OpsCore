#pragma once
#include <cstdint>


namespace oc::ECS {

	// An entity is combination of an id and generation integers
	struct Entity {

		// Define a union of entity and entity* for object pooling
		union {
			uint32_t index;
			uint32_t next;
		};

		uint32_t generation;
	};

	static const Entity INVALID_ENTITY = { 0, 0 };


}