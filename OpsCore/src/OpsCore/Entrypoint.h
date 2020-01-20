#pragma once
#include <stdio.h>

#ifdef OC_PLATFORM_WINDOWS


// Defining as external since we define oc::CreateApplication in the client using OpsCore library. In example case, sandboxapp defines it.
extern oc::Application* oc::CreateApplication();

int main(int argc, char **argv) {

	printf("OpsCore engine started.\n");
	auto app = oc::CreateApplication();
	app->Run();
	delete app;

}

#endif 