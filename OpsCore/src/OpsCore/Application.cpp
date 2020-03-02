
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

		// vertex array
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);
		// vertex buffer
		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f, 0.5f, 0.0f
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * (sizeof(float)), nullptr);
		
		// Element / index buffers
		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer); // to specify order in which to draw vertices in triangle

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		// no need to specify shader, gpus have default

		std::string vertexSrc = R"(

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

			void main(){
				color = vec4(v_Position.x + 0.1, v_Position.y + 0.2, 0.5, 1.0);	
			}

		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
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

			m_Shader->Bind();

			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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