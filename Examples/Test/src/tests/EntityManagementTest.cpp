#include <catch2.hpp>
#include <OpsCore.h>


SCENARIO("Entity creation/deletion", "[ECS]") {

    GIVEN("An ECS::World object and vector of oc::ECS::Entities") {

        oc::ECS::World world;

        WHEN("Creating entities") {
            
            for (int i = 0; i < 10000; i++) {
                world.CreateEntity();
            }

            REQUIRE(world.entities.size() == 10000);
            REQUIRE(world.entities[1000].index == 1000);
            
            world.DestroyEntity(world.entities[999]);

            REQUIRE(world.next_available == 999);

            oc::ECS::Entity t = world.CreateEntity();
            REQUIRE(t.index == 999);
            REQUIRE(t.generation == 1);

            t = world.CreateEntity();
            REQUIRE(t.index == 10000);
            REQUIRE(t.generation == 0);

            for (int i = 100; i < 200; i++) {
                world.DestroyEntity(world.entities[i]);
            }
            
            REQUIRE(world.next_available == 199);
            

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

            for (int i = 0; i < 10000; i++) {
                world.CreateEntity();
            }

            REQUIRE(world.entities.size() == 10000);
            REQUIRE(world.entities[1000].index == 1000);

            world.DestroyEntity(world.entities[999]);

            REQUIRE(world.next_available == 999);

            oc::ECS::Entity t = world.CreateEntity();
            REQUIRE(t.index == 999);
            REQUIRE(t.generation == 1);

            t = world.CreateEntity();
            REQUIRE(t.index == 10000);
            REQUIRE(t.generation == 0);

            for (int i = 100; i < 200; i++) {
                world.DestroyEntity(world.entities[i]);
            }

            REQUIRE(world.next_available == 199);


            for (int i = 199; i > 100; i--) {
                t = world.CreateEntity();
                REQUIRE(t.index == i);
            }

        }

    }
}