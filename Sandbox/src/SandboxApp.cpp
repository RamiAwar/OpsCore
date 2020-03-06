#include "SandboxApp.h"

#include <glm/gtc/matrix_transform.hpp>


// TODO: Refactor this aspect ratio implementation
ExampleLayer::ExampleLayer() : Layer("Example"),
	m_Camera(-oc::Renderer::aspectRatio, oc::Renderer::aspectRatio, -1.0f, 1.0f),
	m_CameraPosition(0.0f)
{
	
	OC_CLIENT_INFO("ExampleLayer: Drawing OpenGL Shapes");

	// Setting up triangle
	triangle_vb.reset(oc::VertexBuffer::Create(triangle_vertices, sizeof(triangle_vertices)));
	triangle_vb->SetLayout(triangleLayout);

	triangle_va.reset(oc::VertexArray::Create());
	triangle_va->AddVertexBuffer(triangle_vb);



	triangle_ib.reset(oc::IndexBuffer::Create(triangle_indices, sizeof(triangle_indices)));
	triangle_va->SetIndexBuffer(triangle_ib);

	// Setting up square
	square_vb.reset(oc::VertexBuffer::Create(square_vertices, sizeof(square_vertices)));
	square_vb->SetLayout(squareLayout);

	square_va.reset(oc::VertexArray::Create());
	square_va->AddVertexBuffer(square_vb);

	square_ib.reset(oc::IndexBuffer::Create(square_indices, sizeof(square_indices)));
	square_va->SetIndexBuffer(square_ib);
	
	triangle_shader.reset(oc::Shader::Create(triangle_vertex_shader_src, triangle_fragment_shader_src));
	square_shader.reset(oc::Shader::Create(square_vertex_shader_src, square_fragment_shader_src));
		

}

void ExampleLayer::OnUpdate(oc::Timestep ds) { 
		
	//OC_CLIENT_INFO("ExampleLayer::Update"); 

	/*if (oc::Input::IsKeyPressed(OC_KEY_TAB)) {

		OC_CLIENT_TRACE("TAB key is pressed");
		
	}*/
		
	oc::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	oc::RenderCommand::Clear();


	oc::Renderer::BeginScene(m_Camera);

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)*scale;
			oc::Renderer::Submit(square_shader, square_va, transform);
		}
	}
	oc::Renderer::Submit(triangle_shader, triangle_va);


	oc::Renderer::EndScene();


	if (oc::Input::IsKeyPressed(OC_KEY_LEFT)) { m_CameraPosition.x -= m_CameraMovementSpeed*ds; }
	else if (oc::Input::IsKeyPressed(OC_KEY_RIGHT)) { m_CameraPosition.x += m_CameraMovementSpeed*ds; }
	
	if (oc::Input::IsKeyPressed(OC_KEY_UP)) { m_CameraPosition.y += m_CameraMovementSpeed*ds; }
	else if (oc::Input::IsKeyPressed(OC_KEY_DOWN)) { m_CameraPosition.y -= m_CameraMovementSpeed*ds; }

	if (oc::Input::IsKeyPressed(OC_KEY_A)) { m_CameraRotation += m_CameraRotationSpeed*ds; }
	else if (oc::Input::IsKeyPressed(OC_KEY_D)) { m_CameraRotation -= m_CameraRotationSpeed*ds; }


	m_Camera.SetRotation(m_CameraRotation);
	m_Camera.SetPosition(m_CameraPosition);
}

void ExampleLayer::OnEvent(oc::Event& event) { 
	//OC_CLIENT_TRACE("{0}", event); 
	
}


void ExampleLayer::OnImGuiRender() {

	static ImGuiID dockspaceID = 0;
	bool active = true;
	if (ImGui::Begin("Master Window", &active))
	{
		ImGui::TextUnformatted("DockSpace below");
	}
	if (active)
	{
		// Declare Central dockspace
		dockspaceID = ImGui::GetID("HUB_DockSpace");
		ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode/*|ImGuiDockNodeFlags_NoResize*/);

	}
	ImGui::End();

	ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Dockable Window"))
	{
		ImGui::TextUnformatted("Test");
		const ImU32 col = ImGui::GetColorU32(ImGuiCol_ButtonHovered);
		const ImU32 bg = ImGui::GetColorU32(ImGuiCol_Button);

		ImGui::Spinner("##spinner", 20.0f, col, bg, 10, 10.0f, 20.0f);
		//ImGui::BufferingBar("##buffer_bar", 0.7f, ImVec2(400, 6), bg, col);
	}
	ImGui::End();

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