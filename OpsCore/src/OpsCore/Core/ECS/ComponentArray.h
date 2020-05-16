#pragma once


#ifdef OC_PLATFORM_WINDOWS
#include <Windows.h>
#endif

#include <stdexcept>

#define DEFAULT_ARRAY_SIZE 100


/**
*	A ComponentArray is an array of components of unknown type (hence the void*).
*	This array is used inside the Archetype structure to house all the components
*	of specific types.
**/
class ComponentArray { // horizontal list of components 

private:
	void* base; // TODO: Work with virtual memory raw packed array
	size_t element_size;
	size_t size; // Number of elements
	size_t space; // How many bytes allocated



public:

	size_t _size() {
		return size;
	}

	size_t _capacity() {
		return space;
	}

	size_t _element_size() {
		return element_size;
	}

	/**
	*	Constructs and allocates a component array with <n_elements> elements, of element size _element_size.
	*	_element_size : sizeof(component)
	*	n_elements : maximum number of elements before resizing ( double this upon resize )
	**/
	ComponentArray(size_t _element_size, size_t n_elements = 1) {
		element_size = _element_size;
		size = 0;
		if (n_elements == 0) {
			space = _element_size * DEFAULT_ARRAY_SIZE;
		}
		else {
			space = n_elements*element_size;
		}

		base = malloc(space);
	}


	/**
	*	ComponentArray copy constructor
	**/
	ComponentArray(const ComponentArray& other)
		: element_size(other.element_size),
		size(other.size),
		space(other.space),
		base(other.base)
	{}

	/** 
	*	Move constructor
	**/
	ComponentArray(ComponentArray&& other)
		:size(other.size),
		space(other.space),
		base(other.base),
		element_size(other.element_size)
	{
		other.base = nullptr;
	}

	ComponentArray& operator=(ComponentArray&& other) {
		if (this != &other) {
			free(base);
			base = other.base;
			size = other.size;
			space = other.space;
			other.base = nullptr;
			other.size = 0;
			other.space = 1;
			return *this;
		}
	}

	ComponentArray& operator=(ComponentArray& other) {
		if (this != &other) {
			free(base);
			base = other.base;
			size = other.size;
			space = other.space;
			return *this;
		}
	}

	void* create_empty_slot() {
		if (size * element_size < space) {
			char* cp = (char*)base;
			size = size + 1;
			return (void*)(cp + (size - 1)* element_size);
		}
		else {
			void* out = realloc(base, space * 2);

			if (out != nullptr) {
				base = out;
				space = space * 2;
			}
			else {
				throw std::exception("ComponentArray: Bad allocation.");
			}

			size = size + 1;
			char* cp = (char*)base;
			return (void*)(cp + (size - 1) * element_size);
		}
	}

	void push_back(void* val)
	{

		if ( size * element_size < space) {
			char* cp = (char*)base;
			memcpy(cp + size * element_size, val, element_size);
		}
		else {
			
			void* out = realloc(base, space * 2);
			
			if (out != nullptr) {
				base = out;
				space = space * 2;
			}
			else {
				throw std::exception("ComponentArray: Bad allocation.");
			}

			char* cp = (char*)base;
			if (cp + size * element_size > 0) {
				memcpy(cp + size * element_size, val, element_size);
			}
		}
		size = size + 1;
	}

	inline void* operator[](int index) {
		return (void*)((char*)base + index*element_size);
	}

	void erase(int index) {
		// Move last element to this index
		if (index < 0 || index > size) return;
		char* cp = (char*)base;
		if (cp + index * element_size > 0) {
			void* val = (void*)((char*)base + (size-1)* element_size);
			memcpy(cp + index * element_size, val, element_size);
			size = size - 1;
		}
	}

	/*inline T& at(int index) {
		if (index < 0) throw std::out_of_range("VVector: Attempt to access negative indices.");
		if (index >= _size) throw std::out_of_range("VVector : Index out of range");
		return base_block[index];
	}*/
};

