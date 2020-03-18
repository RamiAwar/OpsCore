#pragma once
#include <OpsCore.h>

class PlayerController; // forward declaration

class Command {

public:
	virtual ~Command() {}
	virtual void execute(oc::Timestep ts, oc::Ref<PlayerController> controller) = 0;
};