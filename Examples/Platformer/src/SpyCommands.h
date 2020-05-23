#pragma once

#include <PumpkinBox.h>
#include "Command.h"
#include "Components/PlayerController.h"
#include "Components/PlayerAnimationController.h"

class NoCommand : public Command {
public:

	virtual void execute(oc::Timestep ts, oc::Ref<PlayerController> controller) override {}

	// Inherited via Command
	virtual void animate(oc::Timestep ts, oc::Ref<PlayerAnimationController> controller) override {
		controller->Idle(ts);
	}
};

class MoveRightCommand : public Command {
public:

	virtual void execute(oc::Timestep ts, oc::Ref<PlayerController> controller) override {
		controller->MoveRight(ts);
	}

	// Inherited via Command
	virtual void animate(oc::Timestep ts, oc::Ref<PlayerAnimationController> controller) override {
		controller->MoveRight(ts);
	}
};

class MoveLeftCommand : public Command {
public:
	virtual void execute(oc::Timestep ts, oc::Ref<PlayerController> controller) override {
		controller->MoveLeft(ts);
	}
	virtual void animate(oc::Timestep ts, oc::Ref<PlayerAnimationController> controller) override {
		controller->MoveLeft(ts);
	}
};

class SheatheCommand : public Command {
public:
	virtual void execute(oc::Timestep ts, oc::Ref<PlayerController> controller) override {
		controller->Sheathe(ts);
	}
	virtual void animate(oc::Timestep ts, oc::Ref<PlayerAnimationController> controller) override {
		controller->Sheathe(ts);
	}
};
class ShootCommand : public Command {
public:
	virtual void execute(oc::Timestep ts, oc::Ref<PlayerController> controller) override {
		controller->Shoot(ts);
	}
	virtual void animate(oc::Timestep ts, oc::Ref<PlayerAnimationController> controller) override {
		controller->Shoot(ts);
	}
};