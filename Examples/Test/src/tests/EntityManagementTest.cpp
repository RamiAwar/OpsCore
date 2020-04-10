#include <catch2.hpp>
#include <OpsCore.h>


SCENARIO("Entity creation/deletion", "[ECS]") {

    GIVEN("An ECS::World object and vector of oc::ECS::Entities") {

        oc::ECS::World world;

        WHEN("Creating entities") {
            
            for (int i = 0; i < 10000; i++) {
                world.CreateEntity();
            }

            REQUIRE(world._GetEntitySize() == 10000);
            REQUIRE(world._GetEntity(1000).index == 1000);
            
            world.DestroyEntity(world._GetEntity(999));

            REQUIRE(world._GetNextAvailable() == 999);

            oc::ECS::Entity t = world.CreateEntity();
            REQUIRE(t.index == 999);
            REQUIRE(t.generation == 1);

            t = world.CreateEntity();
            REQUIRE(t.index == 10000);
            REQUIRE(t.generation == 0);

            for (int i = 100; i < 200; i++) {
                world.DestroyEntity(world._GetEntity(i));
            }
            
            REQUIRE(world._GetNextAvailable() == 199);
            

            for (int i = 199; i > 100; i--) {
                t = world.CreateEntity();
                REQUIRE(t.index == i);
            }

        }
       
    }
}

SCENARIO("Entity/Component Interaction", "[ECS]") {

    GIVEN("An ECS::World object and vector of oc::ECS::Entities") {

        oc::ECS::World world;
        std::vector<oc::ECS::Entity> entities; // don't need to use my DS here, won't be looping through these
 
        WHEN("Creating entities") {

            

        }

    }
}