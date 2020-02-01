
#include <OpsCore.h>


class ExampleLayer : public oc::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override { 
		//OC_INFO("ExampleLayer::Update"); 
	}

	void OnEvent(oc::Event& event) override { 
		//OC_TRACE("{0}", event); 
	}

};

class Sandbox : public oc::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new oc::ImGuiLayer());
	}

	~Sandbox() {}

};


// Defining CreateApplication in client
oc::Application* oc::CreateApplication() {
	return new Sandbox();
}