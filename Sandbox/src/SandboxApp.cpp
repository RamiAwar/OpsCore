
#include <OpsCore.h>
#include "imgui.h"

class ExampleLayer : public oc::Layer {

private:

	// ------- Triangle inits ---------------------------
	float triangle_vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			 0.0f, 0.5f, 0.0f,  0.2f, 0.8f, 0.8f, 1.0f
	};
	
	uint32_t triangle_indices[3] = { 0, 1, 2 };
	
	oc::BufferLayout triangleLayout = {
		{ oc::ShaderDataType::Float3, "a_pos"},
		{ oc::ShaderDataType::Float4, "a_col"}
	};

	std::shared_ptr<oc::VertexBuffer> triangle_vb;
	std::shared_ptr<oc::VertexArray> triangle_va;
	std::shared_ptr<oc::IndexBuffer> triangle_ib;


	// ----------- Square inits ---------------------------
	float square_vertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f
	};

	uint32_t square_indices[6] = { 0, 1, 2, 2, 3, 1 };

	oc::BufferLayout squareLayout = {
		{oc::ShaderDataType::Float3, "a_pos"}
	};

	std::shared_ptr<oc::VertexBuffer> square_vb;
	std::shared_ptr<oc::VertexArray> square_va;
	std::shared_ptr<oc::IndexBuffer> square_ib;

	std::shared_ptr<oc::Shader> triangle_shader;
	std::shared_ptr<oc::Shader> square_shader;

	std::string triangle_vertex_shader_src = { R"(

			#version 330 core 
			
			layout (location = 0) in vec3 a_Position;
			layout (location = 1) in vec4 a_Color;
			
			out vec3 v_Position;
			out vec4 v_Color;

			void main(){
				v_Position = a_Position*0.5 + 0.5;
				v_Color = a_Color;
				gl_Position = vec4(a_Position.x + 0.5, a_Position.y, a_Position.z, 1.0);	
			}
		)" };
	std::string square_vertex_shader_src = { R"(

			#version 330 core 
			
			layout (location = 0) in vec3 a_Position;
			
			out vec3 v_Position;

			void main(){
				v_Position = a_Position*0.5 + 0.5;
				gl_Position = vec4(a_Position.x + 0.5, a_Position.y, a_Position.z, 1.0);	
			}
		)" };
	std::string triangle_fragment_shader_src = { R"(
			#version 330 core 
			
			layout (location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;

			void main(){
				color = vec4(v_Position.x + 0.1, v_Position.y + 0.2, 0.5, 1.0);	
				color = v_Color;
			}

		)" };
	std::string square_fragment_shader_src = { R"(
			#version 330 core 
			
			layout (location = 0) out vec4 color;
			
			in vec3 v_Position;
			void main(){
				color = vec4(v_Position.x + 0.1, v_Position.y + 0.2, 0.5, 1.0);	
		 	}

		)" };

public:

	ExampleLayer() : Layer("Example") {
		
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
	
		triangle_shader.reset(new oc::Shader(triangle_vertex_shader_src, triangle_fragment_shader_src));
		square_shader.reset(new oc::Shader(square_vertex_shader_src, square_fragment_shader_src));
	
	}

	void OnUpdate() override { 
		
		//OC_CLIENT_INFO("ExampleLayer::Update"); 

		/*if (oc::Input::IsKeyPressed(OC_KEY_TAB)) {

			OC_CLIENT_TRACE("TAB key is pressed");
		}*/
		
		oc::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		oc::RenderCommand::Clear();

		oc::Renderer::BeginScene();

		square_shader->Bind();
		oc::Renderer::Submit(square_va);

		triangle_shader->Bind();
		oc::Renderer::Submit(triangle_va);

		oc::Renderer::EndScene();
		
	}

	void OnEvent(oc::Event& event) override { 
		//OC_CLIENT_TRACE("{0}", event); 
	}

	virtual void OnImGuiRender() override {

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

};

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