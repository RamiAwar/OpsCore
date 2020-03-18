#include "Game.h"


Game::Game(const std::string& name) : Layer("Game"), 
	m_CameraController(oc::Renderer::aspectRatio, false, false) 
{
	spy_texture = oc::Texture2D::Create(spy_texture_path);
}

void Game::OnAttach() {
	//m_GameObjectCollection->OnCreate();

	spy.OnCreate();
}

void Game::OnDetach() {
	//m_GameObjectCollection->OnDestroy();
	spy.OnDestroy();
}

void Game::OnUpdate(oc::Timestep ts) {

	m_CameraController.OnUpdate(ts);

	//m_GameObjectCollection->OnUpdate(ts);
	spy.OnUpdate(ts);
}

void Game::OnLateUpdate(oc::Timestep ts)
{
	spy.OnLateUpdate(ts);
	//m_GameObjectCollection->OnLateUpdate(ts);
}

void Game::OnRender() {

	oc::RenderCommand::SetClearColor({ 0.7f, 0.7f, 0.7f, 1.0f });
	oc::RenderCommand::Clear();

	oc::Renderer2D::BeginScene(m_CameraController.GetCamera());


	//spy.Render();
	//m_GameObjectCollection->Render();

	oc::Renderer2D::DrawSprite(
		sprite_index,
		spy.transform.position, // position
		-0.2f, // size
		spy_texture,
		20, 
		4,
		{ 1.0f, 1.0f }, // tile scale
		{ 1.0f, 1.0f, 1.0f, 1.0f } // color tint
	);



	oc::Renderer2D::EndScene();
}

void Game::OnEvent(oc::Event& event) {
	m_CameraController.OnEvent(event); // pass on events to camera controller
}

void Game::OnImGuiRender() {

	ImGui::Begin("Debug");

	ImGui::Text("Aspect Ratio: %f", oc::Renderer::aspectRatio);
	ImGui::SliderFloat2("Placeholder", glm::value_ptr(placeholder), 0.0f, 1.0f);

	ImGui::DragInt("Index", &sprite_index, 1, 0, 79);

	if (ImGui::Button("Switch")) {
		oc::SceneStateMachine::instance()->SetActive("menu");
	}

	ImGui::End();
}

