#pragma once
#include <OpsCore.h>
#include "Components/PlayerAnimationController.h"

class PlayerController; // forward declaration

class Command {

public:
	virtual ~Command() {}
	virtual void execute(oc::Timestep ts, oc::Ref<PlayerController> controller) = 0;
	virtual void animate(oc::Timestep ts, oc::Ref<PlayerAnimationController> controller) = 0;
};