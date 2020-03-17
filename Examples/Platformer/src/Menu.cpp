#include "Menu.h"


Menu::Menu(const std::string& name) : Layer("Menu"),
	m_CameraController(oc::Renderer::aspectRatio, true, false)
{
	OC_CLIENT_INFO("Initializing menu layer ... ");
}

void Menu::OnAttach() {
	OC_CLIENT_INFO("Inside menu onattach");
}

void Menu::OnDetach() {
	OC_CLIENT_INFO("Inside menu ondetach");
}

void Menu::OnUpdate(oc::Timestep ts) {

	m_CameraController.OnUpdate(ts);

}

void Menu::OnLateUpdate(oc::Timestep ds)
{
	
}

void Menu::OnRender() {

	oc::RenderCommand::SetClearColor({ 0.2f, 0.4f, 0.8f, 1.0f });
	oc::RenderCommand::Clear();

	oc::Renderer2D::BeginScene(m_CameraController.GetCamera());


	oc::Renderer2D::EndScene();
}

void Menu::OnEvent(oc::Event& event) {
	m_CameraController.OnEvent(event); // pass on events to camera controller
}

void Menu::OnImGuiRender() {

	ImGui::Begin("MENU");

	ImGui::Text("Start Game");
	if (ImGui::Button("Start")) {
		oc::SceneStateMachine::instance()->SetActive("demo");
	}

	ImGui::End();
}

