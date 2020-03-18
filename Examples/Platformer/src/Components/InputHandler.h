#pragma once
#include <OpsCore.h>
#include "Command.h"
#include "PlayerController.h"

class MoveRightCommand : public Command {
public:
	virtual void execute(oc::Ref<oc::Component> component) {
		std::dynamic_pointer_cast<PlayerController>(component)->MoveRight();
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

	Command* moveLeftButton;
	Command* moveRightButton = new MoveRightCommand();
	Command* sheatheButton;
	Command* shootButton;

};


