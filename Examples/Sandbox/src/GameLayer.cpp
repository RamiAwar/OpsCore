#include "GameLayer.h"


struct Position {
	float x;
	float y;

	Position()
		:x(0), y(0) {}
};

struct Velocity {
	float x;
	float y;

	Velocity()
		:x(0), y(0) {}

	Velocity(float _x, float _y)
		:x(_x), y(_y) {}
};

struct Player {
	int c;

	Player()
		:c(0) 
	{}
};

class MovementSystem : public pb::ECS::System {

public:
	MovementSystem() : System() {}

	void Update(pb::Timestep ts) override {

		pb::ECS::ComponentIterator<Position> p_iter(&group, 0);
		pb::ECS::ComponentIterator<Velocity> v_iter(&group, 1);

		for (int i = 0; i < p_iter.size(); i++) {
			
			if (pb::Input::IsKeyPressed(PB_KEY_RIGHT))
			{
				p_iter[i]->x += ts * v_iter[i]->x;
			}
			else if (pb::Input::IsKeyPressed(PB_KEY_LEFT))
			{
				p_iter[i]->x -= ts * v_iter[i]->x;
			}


			if (pb::Input::IsKeyPressed(PB_KEY_UP))
			{
				p_iter[i]->y = p_iter[i]->y + ts * v_iter[i]->y;
			}
			else if (pb::Input::IsKeyPressed(PB_KEY_DOWN))
			{
				p_iter[i]->y -= ts * v_iter[i]->y;
			}
			

		}
	}
};

// TODO: Refactor this aspect ratio implementation
GameLayer::GameLayer() : 
	Layer("Example"),
	m_CameraController(pb::Renderer::aspectRatio, true, true, true)
{
	PB_CLIENT_INFO("Constructing GameLayer");
}

void GameLayer::OnAttach()
{
	checkerboard_texture = pb::Texture2D::Create(m_CheckerboardPath);
	mushroom_texture = pb::Texture2D::Create(m_MushroomPath);
	m_Player = m_World.CreateEntity<Position, Velocity>("Player");
	Velocity player_velocity = Velocity(1, 1);
	m_World.SetComponent<Velocity>(m_Player, player_velocity);
	m_World.RegisterSystem<Position, Velocity>(new MovementSystem());
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(pb::Timestep ts)
{
	m_CameraController.OnUpdate(ts);
	m_World.Update(ts);
}

void GameLayer::OnRender() 
{
	pb::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	pb::RenderCommand::Clear();

	pb::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Position* position = m_World.GetComponent<Position>(m_Player);
	pb::Renderer2D::DrawQuad({ position->x, position->y, 0.0f }, // position  
		{ 1.0f, 1.0f }, // size
		checkerboard_blend_color // color
	);

	pb::Renderer2D::DrawQuad({ -1.0f, 1.0f }, // position  
		{ 1.0f, 1.0f }, // size
		{ 0.2f, 0.3f, 0.8f, 1.0f } // color
	);

	pb::Renderer2D::DrawQuad({ 5.0f, 5.0f , 0.1f }, { 10.0f, 10.0f }, checkerboard_texture, { 10.0f, 10.0f }, checkerboard_blend_color);
	pb::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.2f }, { 0.5f, 0.5f }, mushroom_texture);

	pb::Renderer2D::EndScene();
}

void GameLayer::OnEvent(pb::Event& event) 
{
	m_CameraController.OnEvent(event);
}


void GameLayer::OnImGuiRender() {

	

	ImGui::Begin("Scene");
	if (ImGui::TreeNode("Entities"))
	{
		pb::VVector<pb::ECS::Entity>* entities = m_World.GetEntities();
		for (int i = 0; i < entities->size(); i++)
		{
			if (ImGui::TreeNode(m_World.entity_names[(*entities)[i].index].c_str()))
			{
				std::vector<std::string> component_names = m_World.GetComponentNamesList((*entities)[i]);
				for (std::string name : component_names)
				{
					ImGui::Text(name.c_str());
				}

				ImGui::TreePop();
			}
		}
		ImGui::TreePop();
	}
	ImGui::End();

	//
	////if (p_open) { // make settings window closable
	//ImGui::Begin("Settings"/*, &p_open*/);
	//ImGui::Text("Checkboard blend");
	//ImGui::ColorEdit3("", glm::value_ptr(checkerboard_blend_color));

	//if (ImGui::Button("Select Texture Shader")) {
	//	ImGuiFileDialog::Instance()->SetFilterColor(".glsl", ImVec4(0, 1, 0, 0.5));
	//	ImGuiFileDialog::Instance()->OpenDialog("Select Texture Shader", "Choose GLSL File", ".glsl\0", "..");
	//}

	//if (ImGuiFileDialog::Instance()->FileDialog("Select Texture Shader"))
	//{
	//	// action if OK
	//	if (ImGuiFileDialog::Instance()->IsOk == true)
	//	{
	//		m_CheckerboardPath = ImGuiFileDialog::Instance()->GetFilepathName();

	//		// update texture
	//		PB_CLIENT_INFO("Texture shader updated to :'{0}'", m_CheckerboardPath);

	//		auto texture_shader = pb::ShaderLibrary::GetInstance()->Load(m_CheckerboardPath);
	//		m_CheckerboardPath = texture_shader->GetName();

	//		std::dynamic_pointer_cast<pb::OpenGLShader>(texture_shader)->Bind();
	//		std::dynamic_pointer_cast<pb::OpenGLShader>(texture_shader)->UploadUniformInt("u_Texture", 0); // sampler slot = 0 ( default value )
	//	}

	//	//close
	//	ImGuiFileDialog::Instance()->CloseDialog("Select Texture Shader");
	//}

	//ImGui::End();

}


