
#include "ocpch.h"

#include "OpsCore/Input.h"
#include "Application.h"

#include <glad/glad.h>


namespace oc {

	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)


	Application* Application::s_Instance = nullptr;



	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type)
		{
		case oc::ShaderDataType::Float: return GL_FLOAT;
		case oc::ShaderDataType::Float2:return GL_FLOAT;
		case oc::ShaderDataType::Float3:return GL_FLOAT;
		case oc::ShaderDataType::Float4:return GL_FLOAT;
		case oc::ShaderDataType::Mat3:return GL_FLOAT;
		case oc::ShaderDataType::Mat4:return GL_FLOAT;
		case oc::ShaderDataType::Int:return GL_INT;
		case oc::ShaderDataType::Int2:return GL_INT;
		case oc::ShaderDataType::Int3:return GL_INT;
		case oc::ShaderDataType::Int4:return GL_INT;
		case oc::ShaderDataType::Bool:return GL_BOOL;
		default:
			OC_ASSERT(false, "Unknown ShaderDataType!");
			return GL_FALSE;
		}
	}


	Application::Application() {

		OC_ASSERT(!s_Instance, "Application already exists.");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			 0.0f, 0.5f, 0.0f,  0.2f, 0.8f, 0.8f, 1.0f
		};

		// API
		// VertexBuffer buffer = VertexBuffer::Create(sizeof(vertices), vertices);
		// buffer.Bind();

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		
		// Buffer layout API
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color"}
		};

		m_VertexBuffer->SetLayout(layout);

		uint32_t index = 0;
		for (const auto& element : m_VertexBuffer->GetLayout()) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index, 
				element.GetComponentCount(), 
				ShaderDataTypeToOpenGLBaseType(element.type), 
				element.normalized ? GL_TRUE:GL_FALSE, 
				layout.GetStride(), 
				(const void*)element.offset
			);
			index++;
		}


		
		// Element / index buffers
		unsigned int indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		// no need to specify shader, gpus have default

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