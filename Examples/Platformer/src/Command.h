#pragma once
#include <OpsCore.h>

class Command {

public:
	virtual ~Command() {}
	virtual void execute(oc::Ref<oc::Component> component) = 0;
};