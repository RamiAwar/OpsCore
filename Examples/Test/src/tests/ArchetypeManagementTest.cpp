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
            
            Signature signature = World::GenerateSignature<Position, Rotation, RigidBody>();

            REQUIRE(signature.size == 3);

            REQUIRE(signature.component_hashes[0] != signature.component_hashes[1]);
            REQUIRE(signature.component_hashes[0] != signature.component_hashes[2]);

            REQUIRE(signature.component_hashes[0] != signature.hash);
            REQUIRE(signature.component_hashes[1] != signature.hash);
            REQUIRE(signature.component_hashes[2] != signature.hash);

            REQUIRE_THROWS(World::GenerateSignature<Position, Position>());

        }

    }
}
