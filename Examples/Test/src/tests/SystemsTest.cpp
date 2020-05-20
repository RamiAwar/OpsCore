#include <catch2.hpp>
#include <PumpkinBox.h>



using namespace pb::ECS;

SCENARIO("System Addition Test", "[ECS]") {

    GIVEN("A world, an entity, some components") {

        struct Position {
            int x;

            Position()
                :x(5) {}
            Position(int _x) :x(_x) {}
        };

        struct Rotation {
            int y;

            Rotation()
                :y(0) {}
            Rotation(int _y) : y(_y) {}
        };

      


        World world;

        MovementSystem<Position> movementSystem;
        world.RegisterSystem(&movementSystem);

        Entity player = world.CreateEntity<Position, Rotation>();
        


    }

}
