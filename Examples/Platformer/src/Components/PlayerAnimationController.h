#pragma once

#include <OpsCore.h>
#include "SpyStates.h"

class PlayerAnimationController : public oc::AnimationController {

public:

	PlayerAnimationController(oc::GameObject* player) : oc::AnimationController(player) {}

	void OnCreate() override;
	void OnUpdate(oc::Timestep ts) override;
	void Render() override;

	void MoveRight(oc::Timestep ts);
	
	void MoveLeft(oc::Timestep ts);

	void Sheathe(oc::Timestep ts);

	void Shoot(oc::Timestep ts);

	void Idle(oc::Timestep ts);

private:

	SpyAnimationState* m_CurrentAnimationState;

};