#include <catch2.hpp>
#include <windows.h>

#include <OpsCore.h>

#define GB 1000001536

#include <iostream>
using namespace std;


SCENARIO("Custom Memory Allocations", "[memory]") {

    GIVEN("Position struct, empty component array") {
    
        using Position = glm::vec3;

        ComponentArray* arr = new ComponentArray(sizeof(Position));
        
        REQUIRE(arr->_size() == 0);
        REQUIRE(arr->_capacity() == sizeof(Position) * 100);
        REQUIRE(arr->_element_size() == sizeof(Position));

        Position p1(1,2,3);
        arr->push_back(&p1);

        REQUIRE(arr->_size() == 1);
        REQUIRE(arr->_capacity() == sizeof(Position) * 100);
        REQUIRE(arr->_element_size() == sizeof(Position));

        Position* p = (Position*)(*arr)[0];
        REQUIRE(p->x == 1);
        REQUIRE(p->y == 2);
        REQUIRE(p->z == 3);

        Position p2(4, 5, 6);
        for (int i = 0; i < 99; i++) {
            arr->push_back(&p2);
        }

        p = (Position*)(*arr)[99];
        REQUIRE(p->x == 4);
        REQUIRE(p->y == 5);
        REQUIRE(p->z == 6);
        REQUIRE(arr->_size() == 100);
        
        arr->push_back(&p2); // 101th element, reallocation takes place

        p = (Position*)(*arr)[100];
        REQUIRE(p->x == 4);
        REQUIRE(p->y == 5);
        REQUIRE(p->z == 6);
        REQUIRE(arr->_size() == 101);

        for (int i = 0; i < 500; i++) {
            arr->push_back(&p2);
        }

        REQUIRE(arr->_size() == 601);

        arr->erase(0);
        p = (Position*)(*arr)[0];

        REQUIRE(arr->_size() == 600);
        REQUIRE(p->x == 4);
        

    
    }


}


/*
Can someone help me with some void* arithmetic? Can't figure out what's wrong. I'm trying to build a dynamic array class that uses void* (type agnostic, takes in element size).
I'm allocating like this, where space is the amount of memory im reserving:
```
void* base = malloc(_space);
```
Then i push_back like this, where (size) is the index of the last element:
```
size = size + 1;
char* cp = (char*)base;
memcpy(cp + size * element_size, val, element_size);
```
*/

