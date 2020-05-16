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
        archetypes.push_back(empty_archetype);

        REQUIRE(archetypes.size() == 1);
        REQUIRE(archetypes[0].signature == 0);
        REQUIRE(archetypes[0].components.size() == 0);

       

        INFO("Create non-empty Archetype")

        //Metatype* position_metatype = Metatype::BuildMetatype<Position>();
        //Archetype position_archetype = { position_signature, {} };

        ////oc::VVector<Position>* vector_ptr = new oc::VVector<Position>(MB);

        //void* ptr = malloc(sizeof(Position) * 10);
        //ComponentArray position_components(sizeof(Position));

        //position_archetype.components.push_back(position_components);
        //
        //INFO("Adding position component to archetype");
        //// Problem: We don't know type at runtime, so the following will not be doable since Position is unknown
        //// static_cast<oc::VVector<Position>*>(position_archetype.components[0].elements)->push_back({ 1 });
        //// Solution: low level memory management : copy the pointer byte by byte
        //std::memcpy(position_archetype.components[0].elements, position_components.elements, position_components.element_size);

        //// Then client side, we can do this cast!
        //REQUIRE(static_cast<oc::VVector<Position>*>(position_archetype.components[0].elements)->size() == 1);
        //REQUIRE(static_cast<oc::VVector<Position>*>(position_archetype.components[0].elements)->at(0).x == 1);

        //archetypes.push_back(position_archetype);

        //REQUIRE(archetypes.size() == 2);
        //REQUIRE(archetypes[1].signature.size == 1);
        //REQUIRE(archetypes[1].components.size() == 1);

        //ArchetypeNode* position_archetype_node = new ArchetypeNode({ &archetypes[1], {} });

        //INFO("Construct edge between empty and new archetype node with position components");
        //ArchetypeEdge forward_edge;
        //forward_edge.node = position_archetype_node;
        //
        //ArchetypeEdge backward_edge;
        //backward_edge.node = root;
        //
        //forward_edge.component_hash = World::GenerateComponentHash<Position>();
        //backward_edge.component_hash = World::GenerateComponentHash<Position>();

        //root->addition.push_back(forward_edge);
        //position_archetype_node->removal.push_back(backward_edge);

        //REQUIRE(root->addition[0].component_hash == position_archetype_node->archetype->signature.hash);
        //REQUIRE(root->addition[0].component_hash == position_archetype_node->archetype->signature.component_hashes[0]);
        //REQUIRE(root->addition[0].node == position_archetype_node);
        //
        //REQUIRE(position_archetype_node->removal[0].node == root);
        //REQUIRE(position_archetype_node->removal[0].component_hash == position_archetype_node->archetype->signature.hash);
        //
    
    }
}


SCENARIO("World Archetype Add Component Test", "[ECS]") {
    
    GIVEN("A world, an entity, a component") {
    
        struct Position {
            int x;
        };

        struct Rotation {
            int y;
        };

        World world;
        Entity player = world.CreateEntity();

        //world.AddComponent<Position>(player, { 1 });

    }

}
