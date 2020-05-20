#pragma once

#include "PumpkinBox/Core/ECS/System.h"

namespace pb::ECS {
	
    template<typename ...Components>
    class MovementSystem : public System {

    public:
        MovementSystem() :System() {}

        void Update(float delta) override {}
    };

}