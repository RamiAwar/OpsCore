#include <catch2.hpp>
#include <windows.h>

#include <OpsCore.h>

#define GB 1000001536

#include <iostream>
using namespace std;


SCENARIO("Virtual Memory Allocations", "[memory]") {

    GIVEN("1GB of virtual memory reserved, system information fetched") {
        
        oc::VVector<uint32_t> entities(GB);

        WHEN("Array operations performed"){

            INFO("Checking push_back");
            entities.push_back(128);
            REQUIRE(entities[0] == 128);
            REQUIRE(entities._block_offset() == sizeof(uint32_t));
            

            INFO("Checking subscript assignment");
            entities[0] = 500;
            REQUIRE(entities[0] == 500);
            
            INFO("Checking invalid index access");
            REQUIRE_THROWS(entities[1]);

            INFO("Checking erase elements");
            entities.erase(0);
            REQUIRE(entities.size() == 0);
            REQUIRE_THROWS(entities[0]);

        }

        WHEN("More than one page is allocated") {
            
            INFO("Allocating exactly one page");

            for (int i = 0; i < 1024; i++) {
                entities.push_back(i);
            }

            REQUIRE(entities.size() == 1024);
            REQUIRE(entities._block_offset() == 1024 * sizeof(uint32_t));

                   
            INFO("Allocating more than one page");
            REQUIRE(entities._block_offset());
            REQUIRE(entities._block_offset() == entities._page_size());
            REQUIRE(entities.size() == 1024);

            entities.push_back(100);

            REQUIRE(entities.size() == 1025);
        }

        WHEN("Bulk allocating 5000 pages of memory") {

            while (entities._get_page_count() != 5000) {
                entities.push_back(9999);
            }
        }


      /*  WHEN("Bulk allocating half a GB of memory") {
            
            while (entities._get_page_count() != 120000) {
                entities.push_back(1234);
            }
        
        }*/
        

    }
}


