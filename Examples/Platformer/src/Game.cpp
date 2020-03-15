#include "Game.h"


Game::Game() : 
	Layer("Game"), 
	m_CameraController(oc::Renderer::aspectRatio, true, true) 
{
	OC_CLIENT_INFO("Initializing game layer ... ");
}


void Game::OnAttach() {
	spy_texture = oc::Texture2D::Create(spy_texture_path);
}

void Game::OnDetach() {}

void Game::OnUpdate(oc::Timestep ts) {

	m_CameraController.OnUpdate(ts);

	oc::RenderCommand::SetClearColor({ 0.7f, 0.7f, 0.7f, 1.0f });
	oc::RenderCommand::Clear();

	oc::Renderer2D::BeginScene(m_CameraController.GetCamera());

	

	oc::Renderer2D::DrawSprite(
		sprite_index,
		placeholder, // position
		{ 0.4f, 0.4f }, // size
		spy_texture,
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

	ImGui::End();
}

class Main : public oc::Application {
public:
	Main() {
		PushLayer(new Game());
	}

	~Main() {};
};

oc::Application* oc::CreateApplication() {
	return new Main();
}