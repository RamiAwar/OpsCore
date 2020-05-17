#include <catch2.hpp>
#include <PumpkinBox.h>



SCENARIO("Entity creation/deletion", "[ECS]") {

    GIVEN("An ECS::World object and vector of pb::ECS::Entities") {

        pb::ECS::World world;

        WHEN("Creating entities") {
            
            for (int i = 0; i < 10000; i++) {
                world.CreateEntity();
            }

            REQUIRE(world._GetEntitySize() == 10000);
            REQUIRE(world._GetEntity(1000).index == 1000);
            
            world.DestroyEntity(world._GetEntity(999));

            REQUIRE(world._GetNextAvailable() == 999);

            pb::ECS::Entity t = world.CreateEntity();
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

    GIVEN("An ECS::World object and vector of pb::ECS::Entities") {

        pb::ECS::World world;
        
        using Position = glm::vec2;
        using Rotation = float;
        struct Health {
            int max_health;
            int health;

            Health()
                :max_health(5),
                health(max_health) 
            {}
        };

        WHEN("Creating entities") {

            for (int i = 0; i < 10; i++) {
                world.CreateEntity<Position, Rotation>();
            }

            REQUIRE(pb::ECS::metatype_cache.size() == 2);

            world.CreateEntity<Position>();

            REQUIRE(pb::ECS::metatype_cache.size() == 2);

            pb::ECS::Entity e1 = world.CreateEntity<Health>();

            REQUIRE(pb::ECS::metatype_cache.size() == 3);

                
           


        }

    }
}