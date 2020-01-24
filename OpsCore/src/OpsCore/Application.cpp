
#include "ocpch.h"
#include "Application.h"
#include "OpsCore/Events/ApplicationEvent.h"
#include "OpsCore/Log.h"



// TODO: REMOVE FROM HERE
#include <GLFW/glfw3.h>




namespace oc {

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {}

	void Application::Run() {

		while (m_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	
	}

}