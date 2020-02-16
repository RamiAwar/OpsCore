
#include <OpsCore.h>


class ExampleLayer : public oc::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override { 
		//OC_INFO("ExampleLayer::Update"); 

		if (oc::Input::IsKeyPressed(OC_KEY_TAB)) {
			OC_TRACE("TAB key is pressed");
		}

	}

	void OnEvent(oc::Event& event) override { 
		//OC_TRACE("{0}", event); 
	}

};

class Sandbox : public oc::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {}

};


// Defining CreateApplication in client
oc::Application* oc::CreateApplication() {
	return new Sandbox();
}