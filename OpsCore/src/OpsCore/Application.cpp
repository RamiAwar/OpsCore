
#include "ocpch.h"

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
	}

	Application::~Application() {}



	void Application::OnEvent(Event& e) {
		
		EventDispatcher dispatcher(e);
		// If event is window close event, dispatch event to Application::OnWindowClose
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		OC_INFO("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*(--it))->OnEvent(e);
			if (e.m_Handled) break;	// so if overlay handles event, layers will not receive it (ex. clicking button on UI, we don't want click to be propagated into game layer)
		}
	}

	void Application::Run() {

		while (m_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			// Iterate over layers and run update
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

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