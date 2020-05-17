#pragma once
#include <PumpkinBox.h>
#include "Command.h"
#include "PlayerController.h"
#include "SpyCommands.h"

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
	Command* noButton = new NoCommand();
};


