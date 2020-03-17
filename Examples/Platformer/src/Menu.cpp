#include "Menu.h"


Menu::Menu(const std::string& name) : Layer("Menu"),
	m_CameraController(oc::Renderer::aspectRatio, true, false)
{
}

void Menu::OnAttach() {
	pumpkinbox_texture = oc::Texture2D::Create(pumpkinbox_texture_path);
}

void Menu::OnDetach() {}

void Menu::OnUpdate(oc::Timestep ts) {
	m_CameraController.OnUpdate(ts);
}

void Menu::OnLateUpdate(oc::Timestep ds)
{
}

void Menu::OnRender() {

	oc::RenderCommand::SetClearColor({ 0.7f, 0.7f, 0.7f, 1.0f });
	oc::RenderCommand::Clear();

	oc::Renderer2D::BeginScene(m_CameraController.GetCamera());

	oc::Renderer2D::DrawQuad(
		{ 0.5f, 0.5f}, // position
		{ 0.5f, 0.5f }, // size
		//pumpkinbox_texture,
		//{ 1.0f, 1.0f }, // tile scale
		{ 1.0f, 1.0f, 1.0f, 1.0f } // color tint
	);

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

