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

            void Update(pb::Timestep ts) override {
                
                ComponentIterator<Position> p_iter(&group, 0);
                for (int i = 0; i < p_iter.size(); i++) {
                    p_iter[i]->x++;
                }
            }
        };
         
        World world;

        Entity player = world.CreateEntity<Position, Rotation>();
        Position* player_position = world.GetComponent<Position>(player);

        MovementSystem movementSystem;
        
        REQUIRE(0 == movementSystem.group.matched_archetypes.size());
        REQUIRE(0 == System::instance_list.size());
        
        world.RegisterSystem<Position, Rotation>(&movementSystem);

        REQUIRE(1 == movementSystem.group.matched_archetypes.size());
        REQUIRE(1 == System::instance_list.size());

        REQUIRE(0 == player_position->x);

        movementSystem.Update(0);
        
        REQUIRE(1 == player_position->x);

        class AdvancedMovementSystem : public System {

        public:
            AdvancedMovementSystem() : System() {}

            void Update(pb::Timestep ts) override {
                ComponentIterator<Position> p_iter(&group, 0);
                for (int i = 0; i < p_iter.size(); i++) {
                    p_iter[i]->x++;
                }
            }
        };

        struct Tag {
            int z;
            Tag() :z(0) {}

        };

        Entity enemy = world.CreateEntity<Position, Rotation, Tag>();
        Entity transform = world.CreateEntity<Position>();

        AdvancedMovementSystem advanced_move;
        world.RegisterSystem<Position>(&advanced_move);

        REQUIRE(2 == System::instance_list.size());
        REQUIRE(3 == advanced_move.group.matched_archetypes.size());

        Position* enemy_position = world.GetComponent<Position>(enemy);
        Position* transform_position = world.GetComponent<Position>(transform);

        REQUIRE(0 == enemy_position->x);
        
        advanced_move.Update(0);

        REQUIRE(1 == enemy_position->x);

        advanced_move.Update(0);

        REQUIRE(2 == enemy_position->x);
        REQUIRE(2 == transform_position->x);
          

        

    }

}
