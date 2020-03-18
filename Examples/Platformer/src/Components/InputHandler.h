#pragma once
#include <OpsCore.h>
#include "Command.h"
#include "PlayerController.h"

class MoveRightCommand : public Command {
public:
	virtual void execute(oc::Timestep ts, oc::Ref<PlayerController> controller) override {
		controller->MoveRight(ts);
	}
};

class MoveLeftCommand : public Command {
public:
	virtual void execute(oc::Timestep ts, oc::Ref<PlayerController> controller) override {
		controller->MoveLeft(ts);
	}
};

class SheatheCommand : public Command {
public:
	virtual void execute(oc::Timestep ts, oc::Ref<PlayerController> controller) override {
		controller->Sheathe(ts);
	}
};
class ShootCommand : public Command {
public:
	virtual void execute(oc::Timestep ts, oc::Ref<PlayerController> controller) override {
		controller->Shoot(ts);
	}
};


class InputHandler : public oc::Component
{
public:

	InputHandler(oc::GameObject* parent) : oc::Component(parent) // initializes parent object
	{ 
	}

	void OnCreate() override {}
	void OnDestroy() override {}

	void OnEvent(oc::Event& e) override {}
	void OnUpdate(oc::Timestep ts) override {}
	void OnLateUpdate(oc::Timestep ts) override {}
	void Render() override {}


	Command* HandleInput();

private:

	Command* moveLeftButton = new MoveLeftCommand();
	Command* moveRightButton = new MoveRightCommand();
	Command* sheatheButton = new SheatheCommand();
	Command* shootButton = new ShootCommand();

};


