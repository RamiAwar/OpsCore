#pragma once

#include "OpsCore/Core.h"
#include "Events/Event.h"
#include "OpsCore/Events/ApplicationEvent.h"

#include "Window.h"

namespace oc {

	class OPSCORE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void Run();
	private:

		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// Define in client
	Application* CreateApplication();

}

