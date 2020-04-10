#pragma once
#include "OpsCore/Core/VVector.h"

#define MAX_COMPONENTS 32


namespace oc::ECS {

	/**
	*	Hashing function to hash strings into unsigned integers. This will allow
	*	Components to have a signature integer deduced from their typename, and
	*	will allow Archetypes to have a signature integer that indicates which 
	*	components are included inside of it.
	**/
	inline constexpr uint64_t hash_fnv1a(const char* key) {

		uint64_t hash = 0xcbf29ce484222325;
		uint64_t prime = 0x100000001b3;

		int i = 0;
		while (key[i]) {
			uint8_t value = key[i++];
			hash = hash ^ value;
			hash *= prime;
		}

		return hash;

	}

	/**
	*	A Signature is a struct that houses the hashing of the different component
	*	types inside an archetype so we can quickly identify it (hash). It also contains
	*	the hashes of all components that are grouped by this archetype (component_hashes).
	*	The fields have to be manually populated due to the decision to keep these structures lightweight.
	*	This would help keep them available in CPU caches by not taking up too much space.
	**/
	struct Signature {

		// Stores a list of Component Hashes
		// Has to be manually populated
		uint64_t component_hashes[MAX_COMPONENTS];

		// Stores combined (XORed) ComponentHash
		// Has to be manually set
		uint64_t hash;

		// Number of components 
		// Has to be manually updated when handling archetypes (creation, destruction)
		size_t size;

	};

	/**
	*	A ComponentArray is an array of components of unknown type (hence the void*).
	*	This array is used inside the Archetype structure to house all the components 
	*	of specific types.
	**/
	struct ComponentArray {
		void* elements;
		size_t size;
	};


	/**
	*	An archetype houses all entities that have the same set of components
	*	A key idea in designing this struct is keeping it lightweight. All functionality
	*	is moved to the World class which manages Archetypes.
	**/
	struct Archetype {

		Signature signature;
		VVector<ComponentArray> components;

	};

}