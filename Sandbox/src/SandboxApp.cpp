#include <OpsCore.h>


class Sandbox : public oc::Application {
public:
	Sandbox() {}

	~Sandbox() {}

};

int main() {

	Sandbox* sandbox = new Sandbox(); // allocate on the heap
	sandbox->Run();

	delete sandbox;
}