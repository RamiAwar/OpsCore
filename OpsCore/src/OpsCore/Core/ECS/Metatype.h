#pragma once
#include <cstdint>
#include <unordered_map>

namespace oc::ECS {
	/**
		*	A Metatype is a struct that houses the hash and size of an individual component.
		*	The hash is simply typeid(T).hash.
		*	The size is the size in bytes of the struct it represents.
		**/
	struct Metatype {

		uint16_t size{ 0 };
		uint64_t hash;

		friend bool operator== (const Metatype& a, const Metatype& b) {
			return a.hash == b.hash;
		}

		friend bool operator< (const Metatype& a, const Metatype& b) {
			return a.hash < b.hash;
		}

		template<typename T>
		static Metatype* BuildMetatype() {

			size_t hash = typeid(T).hash_code();

			if (metatype_cache.find(hash) == metatype_cache.end()) {
				Metatype m;
				m.size = sizeof(T);
				m.hash = hash;
				metatype_cache[hash] = m;
			}

			return &metatype_cache[hash];
		}

	};

	/**
	*	Metatype sorter
	**/
	inline void sort_metatypes(const Metatype** types, size_t count) {
		std::sort(types, types + count, [](const Metatype* a, const Metatype* b) {
			return a < b;
		});
	}

	/**
	*	Static map to store metatypes uniquely
	**/
	static std::unordered_map<uint64_t, Metatype> metatype_cache;

	/**
	*	Hashing function to hash strings into unsigned integers. This will allow
	*	Components to have a signature integer deduced from their typename, and
	*	will allow Archetypes to have a signature integer that indicates which
	*	components are included inside of it.
	**/
	inline constexpr uint64_t hash_fnv1a(const Metatype** metatypes, size_t count) {

		uint64_t hash = 0xcbf29ce484222325;
		uint64_t prime = 0x100000001b3;

		int i = 0;
		while (i < count) {
			uint64_t component_hash = metatypes[i++]->hash;
			hash = hash ^ component_hash;
			hash *= prime;
		}

		return hash;

	}
}