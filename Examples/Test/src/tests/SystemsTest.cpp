#include <catch2.hpp>
#include <PumpkinBox.h>



using namespace pb::ECS;

SCENARIO("System Addition Test", "[ECS]") {

    GIVEN("A world, an entity, some components") {

        struct Position {
            int x;

            Position()
                :x(0) {}
            Position(int _x) :x(_x) {}
        };

        struct Rotation {
            int y;

            Rotation()
                :y(0) {}
            Rotation(int _y) : y(_y) {}
        };

	
        class MovementSystem : public System {

        public:
            MovementSystem() : System() {}

            void Update(float delta) override {
                
                //for (Archetype* arch : group.archetypes) {
                //
                //    uint64_t hash = typeid(Position).hash_code();
                //    // Find the component index 
                //    for (int i = 0; i < arch->n_types; i++) {
                //        // If this is the component type we are looking for,
                //        if (hash == arch->types[i]->hash) {
                //            // Component array found, iterate over all
                //            for (int j = 0; j < arch->components[i]._size(); j++) {

                //                ((Position*)(arch->components[i][j]))->x++;
                //            }
                //        }
                //    }
                //}

                ComponentIterator<Position> p_iter(&group);
                p_iter[0]->x++;
            }
        };

        World world;

        Entity player = world.CreateEntity<Position, Rotation>();
        Position* player_position = world.GetComponent<Position>(player);

        MovementSystem movementSystem;
        
        REQUIRE(0 == movementSystem.group.archetypes.size());
        REQUIRE(0 == System::instance_list.size());
        
        world.RegisterSystem<Position, Rotation>(&movementSystem);

        REQUIRE(1 == movementSystem.group.archetypes.size());
        REQUIRE(1 == System::instance_list.size());

        REQUIRE(0 == player_position->x);
        movementSystem.Update(0);
        REQUIRE(1 == player_position->x);


    }

}
