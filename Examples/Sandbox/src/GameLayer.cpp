#include "GameLayer.h"


struct Position {
	int x;
	int y;

	Position()
		:x(0), y(0) {}
};

// TODO: Refactor this aspect ratio implementation
GameLayer::GameLayer() : Layer("Example"),
m_CameraController(pb::Renderer::aspectRatio, true, true, true)
{
	PB_CLIENT_INFO("Constructing GameLayer");
}

void GameLayer::OnAttach()
{
	checkerboard_texture = pb::Texture2D::Create(m_CheckerboardPath);
	mushroom_texture = pb::Texture2D::Create(m_MushroomPath);
	m_Player = m_World.CreateEntity<Position>("Player");
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(pb::Timestep ts)
{
	m_CameraController.OnUpdate(ts);
}

void GameLayer::OnRender() 
{
	pb::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	pb::RenderCommand::Clear();

	pb::Renderer2D::BeginScene(m_CameraController.GetCamera());

	pb::Renderer2D::DrawQuad({ 0.3f, 0.0f, 0.0f }, // position  
		{ 2.0f, 2.0f }, // size
		checkerboard_blend_color // color
	);

	pb::Renderer2D::DrawQuad({ -1.0f, 1.0f }, // position  
		{ 1.0f, 1.0f }, // size
		{ 0.2f, 0.3f, 0.8f, 1.0f } // color
	);

	pb::Renderer2D::DrawQuad({ 0.5f, 0.5f , 0.1f }, { 10.0f, 10.0f }, checkerboard_texture, { 10.0f, 10.0f }, checkerboard_blend_color);
	pb::Renderer2D::DrawQuad({ 0.2f, 0.4f, 0.2f }, { 0.5f, 0.5f }, mushroom_texture);

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


