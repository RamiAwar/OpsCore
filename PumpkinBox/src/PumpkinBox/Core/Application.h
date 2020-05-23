#pragma once

#include "PumpkinBox/Core/Core.h"
#include "PumpkinBox/Core/Window.h"

#include "PumpkinBox/Events/Event.h"
#include "PumpkinBox/Events/ApplicationEvent.h"

#include "PumpkinBox/Core/Timestep.h"

#include "PumpkinBox/Core/Scene.h"

namespace pb {

	class  Application{

	public:

		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void Run();

		inline static Application& Get() { return *s_Instance; }
		inline  Window& GetWindow() { return *m_Window; }

	protected:
		std::unique_ptr<Window> m_Window;


	private:

		static Application* s_Instance;

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		bool m_Running = true;
		bool m_Minimized = false;
		float m_LastDeltaTime = 0.0f;

	};

	// Define in client
	Application* CreateApplication();

}

