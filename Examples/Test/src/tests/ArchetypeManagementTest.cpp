#include <catch2.hpp>
#include <OpsCore.h>


using namespace oc::ECS;

SCENARIO("Archetype Signature Test", "[ECS]") {

    GIVEN("Some component structs") {

        struct Position {
            int x;
        };
        struct Rotation {
            int y;
        };
        struct RigidBody {
            int z;
        };

        WHEN("A signature is generated from these structs") {
            
           /* Signature signature = World::GenerateSignature<Position, Rotation, RigidBody>();

            REQUIRE(signature.size == 3);

            REQUIRE(signature.component_hashes[0] != signature.component_hashes[1]);
            REQUIRE(signature.component_hashes[0] != signature.component_hashes[2]);

            REQUIRE(signature.component_hashes[0] != signature.hash);
            REQUIRE(signature.component_hashes[1] != signature.hash);
            REQUIRE(signature.component_hashes[2] != signature.hash);

            REQUIRE_THROWS(World::GenerateSignature<Position, Position>());*/

        }

    }
}

SCENARIO("Archetype Creation Test", "[ECS]") {

    GIVEN("Some component structs and an entity") {

        struct Position {
            int x;
        };

        struct Rotation {
            int y;
        };

        struct RigidBody {
            int z;
        };

        World world;
        Entity player = world.CreateEntity<Position, Rotation, RigidBody>();
        oc::VVector<Archetype> archetypes(500*MB);
        

        INFO("Create empty Archetype and ArchetypeNode")

        // Create empty archetype
        
        Archetype empty_archetype = { 0, {} };
        archetypes.push_back(std::move(empty_archetype));

        REQUIRE(archetypes.size() == 1);
        REQUIRE(archetypes[0].signature == 0);
        REQUIRE(archetypes[0].components.size() == 0);

       

        INFO("Create non-empty Archetype")

        Metatype* position_metatype = Metatype::BuildMetatype<Position>();
        Archetype position_archetype = { position_metatype->hash, {} };

        INFO("Adding position component to archetype");
        ComponentArray position_components(sizeof(Position), 50000); // Make room for 50,000 entities out of the box
        position_archetype.components.push_back(std::move(position_components)); // Add component array to archetype
       
        archetypes.push_back(std::move(position_archetype));
       
        REQUIRE(archetypes.size() == 2);
        REQUIRE(archetypes[1].signature == position_metatype->hash);
        REQUIRE(archetypes[1].components.size() == 1);
       


    }
}


SCENARIO("World Archetype Add Component Test", "[ECS]") {
    
    GIVEN("A world, an entity, a component") {
    
        struct Position {
            int x;

            Position()
                :x(5){}
        };

        struct Rotation {
            int y;
        };

        World world;

        Entity player = world.CreateEntity<Position, Rotation>();
        Position* player_position = world.GetComponent<Position>(player);

        REQUIRE(player_position->x == 5);

        player_position->x += 10;

        REQUIRE(player_position->x == 15);
        REQUIRE(world.GetComponent<Position>(player)->x == 15);



    }

}
