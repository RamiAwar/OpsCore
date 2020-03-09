#pragma once

#include "OpsCore/Core/Core.h"
#include "OpsCore/Core/Window.h"

#include "OpsCore/Core/LayerStack.h"
#include "OpsCore/Events/Event.h"
#include "OpsCore/Events/ApplicationEvent.h"

#include "OpsCore/ImGui/ImGuiLayer.h"

#include "OpsCore/Renderer/Shader.h"
#include "OpsCore/Renderer/Buffer.h"
#include "OpsCore/Renderer/VertexArray.h"

#include "OpsCore/Core/Timestep.h"

namespace oc {

	class  Application{

	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		// TODO: Pop layers functionality

		inline static Application& Get() { return *s_Instance; }
		inline  Window& GetWindow() { return *m_Window; }

	private:

		static Application* s_Instance;

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;

		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		bool m_Minimized = false;

		LayerStack m_LayerStack;

		float m_LastDeltaTime = 0.0f;


	};

	// Define in client
	Application* CreateApplication();

}

