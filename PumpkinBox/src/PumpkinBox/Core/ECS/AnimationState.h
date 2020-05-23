#pragma once

#include "PumpkinBox/Core/GameObject.h"

namespace pb {

	class AnimationState {

	public:
		
		virtual void enter(GameObject*)=0;
		virtual void update(pb::Timestep ts, GameObject*)=0;

	};
}