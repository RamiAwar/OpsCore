#pragma once
#include "OpsCore/Core/Core.h"



// Defining as external since we define oc::CreateApplication in the client using OpsCore library. In example case, sandboxapp defines it.
extern oc::Application* oc::CreateApplication();

int main(int argc, char **argv) {


	//TODO: Replace with engine initialization function
	oc::Log::Init();
	OC_TRACE("OpsCore Engine started.");

	OC_INFO("Welcome to OpsCore.");

	auto app = oc::CreateApplication();
	app->Run();
	delete app;

}

// #endif 

