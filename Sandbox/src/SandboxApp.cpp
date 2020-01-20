#include <OpsCore.h>


class Sandbox : public oc::Application {
public:
	Sandbox() {}

	~Sandbox() {}

};


// Defining CreateApplication in client
oc::Application* oc::CreateApplication() {
	return new Sandbox();
}