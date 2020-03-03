
#include "ocpch.h"

#include "OpsCore/Input.h"
#include "Application.h"

#include <glad/glad.h>


namespace oc {

	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)


	Application* Application::s_Instance = nullptr;

	Application::Application() {

		OC_ASSERT(!s_Instance, "Application already exists.");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);


		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			 0.0f, 0.5f, 0.0f,  0.2f, 0.8f, 0.8f, 1.0f
		};

		
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		{
			// Buffer layout API
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float4, "a_Color"}
			};

			m_VertexBuffer->SetLayout(layout);
		}

		// After layout has been set, create vertex array
		m_VertexArray.reset(VertexArray::Create());
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		// Element / index buffers
		unsigned int indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);


		m_SquareVertexArray.reset(VertexArray::Create());

		float square_vertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(VertexBuffer::Create(square_vertices, sizeof(square_vertices)));

		squareVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
		});
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t square_indices[6] = { 0, 1, 2, 2, 3, 1 };
		std::shared_ptr<IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(IndexBuffer::Create(square_indices, sizeof(square_indices)));
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);



		std::string vertexSrc = R"(

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
		)";

		std::string squareVertexShaderSrc = R"(

			#version 330 core 
			
			layout (location = 0) in vec3 a_Position;
			
			out vec3 v_Position;

			void main(){
				v_Position = a_Position*0.5 + 0.5;
				gl_Position = vec4(a_Position.x + 0.5, a_Position.y, a_Position.z, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core 
			
			layout (location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;

			void main(){
				color = vec4(v_Position.x + 0.1, v_Position.y + 0.2, 0.5, 1.0);	
				color = v_Color;
			}

		)";

		std::string squareFragmentShaderSrc = R"(
			#version 330 core 
			
			layout (location = 0) out vec4 color;
			
			in vec3 v_Position;
			void main(){
				color = vec4(v_Position.x + 0.1, v_Position.y + 0.2, 0.5, 1.0);	
			}

		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
		m_SquareShader.reset(new Shader(squareVertexShaderSrc, squareFragmentShaderSrc));
	}

	Application::~Application() {}



	void Application::OnEvent(Event& e) {
		
		EventDispatcher dispatcher(e);
		// If event is window close event, dispatch event to Application::OnWindowClose
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		//OC_INFO("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*(--it))->OnEvent(e);
			if (e.m_Handled) break;	// so if overlay handles event, layers will not receive it (ex. clicking button on UI, we don't want click to be propagated into game layer)
		}
	}

	void Application::Run() {

		while (m_Running) {
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_SquareShader->Bind();
			m_SquareVertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_SquareVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
			
			
			m_Shader->Bind();
			m_VertexArray->Bind();

			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			// Iterate over layers and run update
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) {
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();

	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

}