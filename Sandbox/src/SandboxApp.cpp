#include "SandboxApp.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


float ExampleLayer::m_FPS = 0.0f;
int ExampleLayer::fps_counter = 0;

// TODO: Refactor this aspect ratio implementation
ExampleLayer::ExampleLayer() : Layer("Example"),
	m_CameraController(oc::Renderer::aspectRatio, true)
{
	OC_CLIENT_INFO("Constructing ExampleLayer");
}

void ExampleLayer::OnAttach() 
{
	checkerboard_texture = oc::Texture2D::Create(m_CheckerboardPath);
	mushroom_texture = oc::Texture2D::Create(m_MushroomPath);
}

void ExampleLayer::OnDetach() 
{

}

void ExampleLayer::OnUpdate(oc::Timestep ts) 
{ 
		
	// UPDATE
	m_CameraController.OnUpdate(ts);
	
	// TODO: do more efficiently
	// FPS counting
	fps_counter++;
	if(fps_counter % 50 == 0) m_FPS = 1.0f / ts;
	if (fps_counter > 10000000) fps_counter = 0;


	// RENDER
	oc::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	oc::RenderCommand::Clear();


	oc::Renderer2D::BeginScene(m_CameraController.GetCamera());

	/*glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)*scale;

			if((i+j)%2 == 0){
				std::dynamic_pointer_cast<oc::OpenGLShader>(square_shader)->UploadUniformFloat3("u_Color", m_RedColor);
				oc::Renderer::Submit(square_shader, square_va, transform);
			}else{
				std::dynamic_pointer_cast<oc::OpenGLShader>(square_shader)->UploadUniformFloat3("u_Color", m_BlueColor);
				oc::Renderer::Submit(square_shader, square_va, transform);
			}
		
		}
	}*/

	oc::Renderer2D::DrawQuad({ 0.5f, 0.5f }, { 10.0f, 10.0f }, checkerboard_texture);

	oc::Renderer2D::DrawQuad({ 0.3f, 0.0f }, // position  
							 { 1.0f, 1.0f }, // size
							 { 0.8f, 0.2f, 0.3f, 1.0f } // color
							); 

	oc::Renderer2D::DrawQuad({ -1.0f, 0.0f }, // position  
		{ 0.8f, 1.4f }, // size
		{ 0.2f, 0.3f, 0.8f, 1.0f } // color
	);

	oc::Renderer2D::DrawQuad({ 0.2f, 0.4f }, { 0.5f, 0.5f }, mushroom_texture);

	oc::Renderer2D::EndScene();


	
}

void ExampleLayer::OnEvent(oc::Event& event) { 
	//OC_CLIENT_TRACE("{0}", event);
	m_CameraController.OnEvent(event);
}


void ExampleLayer::OnImGuiRender() {

	// ------- Color Settings Menu ---------
	static bool p_open = true; // has to be static because this is called every frame. 
	/* each time the function is called the static variable will maintain the last
	value it had at the end of the previous function call. */

	static bool display_dialog = false;

	//if (p_open) { // make settings window closable
		//ImGui::Begin("Settings"/*, &p_open*/);
		/*ImGui::ColorEdit3("Color 1", glm::value_ptr(m_RedColor));
		ImGui::ColorEdit3("Color 2", glm::value_ptr(m_BlueColor));*/

		//if (ImGui::Button("Select Texture Shader")) {
		//	ImGuiFileDialog::Instance()->SetFilterColor(".glsl", ImVec4(0, 1, 0, 0.5));
		//	ImGuiFileDialog::Instance()->OpenDialog("Select Texture Shader", "Choose GLSL File", ".glsl\0", "..");
		//}

		//if (ImGuiFileDialog::Instance()->FileDialog("Select Texture Shader"))
		//{
		//	// action if OK
		//	if (ImGuiFileDialog::Instance()->IsOk == true)
		//	{
		//		m_TextureShaderPath = ImGuiFileDialog::Instance()->GetFilepathName();

		//		// update texture
		//		OC_CLIENT_INFO("Texture shader updated to :'{0}'", m_TextureShaderPath);

		//		auto texture_shader = m_ShaderLibrary.Load(m_TextureShaderPath);
		//		m_CurrentShader = texture_shader->GetName();

		//		std::dynamic_pointer_cast<oc::OpenGLShader>(texture_shader)->Bind();
		//		std::dynamic_pointer_cast<oc::OpenGLShader>(texture_shader)->UploadUniformInt("u_Texture", 0); // sampler slot = 0 ( default value )

		//	}

			// close
		//	ImGuiFileDialog::Instance()->CloseDialog("Select Texture Shader");
		//}

		//ImGui::Text("Main Texture: (%s)", m_TexturePath.c_str());
		// TODO: This conversion is OpenGL specific. Must abstract it away. (uint32_t to (void*)(intptr_t))
		//ImGui::Image((void*)(intptr_t)texture->GetRendererID(), ImVec2(100, 100));

		//if (ImGui::Button("Select Texture")) {
		//	ImGuiFileDialog::Instance()->SetFilterColor(".png", ImVec4(0, 1, 0, 0.5));
		//	ImGuiFileDialog::Instance()->OpenDialog("Select Texture", "Choose File", ".png\0", "..");
		//}

		//if (ImGuiFileDialog::Instance()->FileDialog("Select Texture"))
		//{
		//	// action if OK
		//	if (ImGuiFileDialog::Instance()->IsOk == true)
		//	{
		//		m_TexturePathName = ImGuiFileDialog::Instance()->GetFilepathName();
		//		
		//		// update texture
		//		OC_CLIENT_INFO("Texture path updated to :'{0}'", m_TexturePathName);
		//		texture = oc::Texture2D::Create(m_TexturePathName);
		//	}

			// close
		//	ImGuiFileDialog::Instance()->CloseDialog("Select Texture");
		//}

		//ImGui::End();

	ImGui::Begin("Stats");
	ImGui::Text("FPS: %.2f", m_FPS);
	ImGui::End();

	//}

	// ------- ImGui Dockspace -------------
	 //static ImGuiID dockspaceID = 0;
	 //bool active = true;
	 //if (ImGui::Begin("Master Window", &active))
	 //{
	 //	ImGui::TextUnformatted("DockSpace below");
	 //}
	 //if (active)
	 //{
	 //	// Declare Central dockspace
	 //	dockspaceID = ImGui::GetID("HUB_DockSpace");
	 //	ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode/*|ImGuiDockNodeFlags_NoResize*/);

	 //}
	 //ImGui::End();

	 //ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);
	 //if (ImGui::Begin("Dockable Window"))
	 //{
	 //	ImGui::TextUnformatted("Test");
	 //	const ImU32 col = ImGui::GetColorU32(ImGuiCol_ButtonHovered);
	 //	const ImU32 bg = ImGui::GetColorU32(ImGuiCol_Button);

	 //	ImGui::Spinner("##spinner", 20.0f, col, bg, 10, 10.0f, 20.0f);
	 //	//ImGui::BufferingBar("##buffer_bar", 0.7f, ImVec2(400, 6), bg, col);
	 //}
	 //ImGui::End();

}



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