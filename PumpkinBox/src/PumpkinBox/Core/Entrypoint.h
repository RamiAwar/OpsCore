#pragma once
#include "PumpkinBox/Core/Core.h"



// Defining as external since we define oc::CreateApplication in the client using PumpkinBox library. In example case, sandboxapp defines it.
extern pb::Application* pb::CreateApplication();

int main(int argc, char **argv) {


	//TODO: Replace with engine initialization function
	pb::Log::Init();
	PB_TRACE("PumpkinBox Engine started.");

	PB_INFO("Welcome to PumpkinBox.");

	auto app = pb::CreateApplication();
	app->Run();
	delete app;

}

// #endif 

