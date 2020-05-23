#pragma once
#include "PumpkinBox/Core/Core.h"



// Defining as external since we define oc::CreateApplication in the client using PumpkinBox library. In example case, sandboxapp defines it.
extern pb::Application* pb::CreateApplication();

int main(int argc, char **argv) {


	//TODO: Replace with engine initialization function
	pb::Log::Init();
	PB_TRACE("PumpkinBox Engine started.");

	PB_INFO("Welcome to PumpkinBox.");

	PB_PROFILE_BEGIN_SESSION("Startup", "PumpkinBoxProfile-Startup.json");
	auto app = pb::CreateApplication();
	PB_PROFILE_END_SESSION();


	PB_PROFILE_BEGIN_SESSION("Runtime", "PumpkinBoxProfile-Runtime.json");
	app->Run();
	PB_PROFILE_END_SESSION();

	PB_PROFILE_BEGIN_SESSION("Shutdown", "PumpkinBoxProfile-Shutdown.json");
	delete app;
	PB_PROFILE_END_SESSION();

}

// #endif 

