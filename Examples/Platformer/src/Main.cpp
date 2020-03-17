#include "Game.h"
#include "Menu.h"

// ------- Entry point -----------
#include "OpsCore/Core/Entrypoint.h"

class DemoScene : public oc::Scene {
public:
	DemoScene(){}

	void OnAttach() {
		PushLayer(new Game());
	}

	~DemoScene() {};

};

class SplashScreenScene : public oc::Scene {
public:
	SplashScreenScene() {}

	void OnAttach() {
		PushLayer(new Menu());
	}

	~SplashScreenScene() {};
	
};
	

class Main : public oc::Application {
public:

	Main() {
		
		oc::SceneStateMachine::instance()->Add("menu", oc::CreateRef<SplashScreenScene>());
		
		oc::SceneStateMachine::instance()->Add("demo", oc::CreateRef<DemoScene>());

	}

	~Main() {};

};

oc::Application* oc::CreateApplication() {
	return new Main();
}