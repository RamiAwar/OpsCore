#pragma once

#include "OpsCore/Core/GameObject.h"

namespace oc {

	class AnimationState {

	public:
		
		virtual void enter(GameObject*)=0;
		virtual void update(oc::Timestep ts, GameObject*)=0;

	};
}