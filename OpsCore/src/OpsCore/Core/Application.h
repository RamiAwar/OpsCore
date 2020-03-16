#pragma once

#include "OpsCore/Core/Core.h"
#include "OpsCore/Core/Window.h"

#include "OpsCore/Events/Event.h"
#include "OpsCore/Events/ApplicationEvent.h"

#include "OpsCore/Core/Timestep.h"

#include "OpsCore/Core/Scene.h"

namespace oc {

	class  Application{

	public:

		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void Run();

		inline static Application& Get() { return *s_Instance; }
		inline  Window& GetWindow() { return *m_Window; }

	protected:
		Scene* m_ActiveScene;
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

