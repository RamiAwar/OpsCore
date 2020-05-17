#pragma once

#include "PumpkinBox/Core/Core.h"

#include "PumpkinBox/Core/LayerStack.h"
#include "PumpkinBox/Events/Event.h"
#include "PumpkinBox/ImGui/ImGuiLayer.h"

#include "PumpkinBox/Core/Timestep.h"


namespace pb {

	class Scene
	{

	public:

		Scene() : m_Shutdown(false) { m_LayerStack = new LayerStack(); }

		virtual void OnInit();
		virtual void OnAttach();
		virtual void OnDetach();

		virtual void OnEvent(Event& e);

		// TODO: Change boolean minimized to a struct representing various window properties
		virtual void OnUpdate(pb::Timestep ts, bool minimized);

		virtual void PushLayer(Layer* layer);
		virtual void PushOverlay(Layer* layer);
		
		void ToggleShutdown();
		inline bool GetShutdown() { return m_Shutdown; }


	protected:

		// TODO: Change ImGuiLayer to removable layer, not forced initialization 
		static ImGuiLayer* m_ImGuiLayer; 
		LayerStack* m_LayerStack; // necessary to initialize to instance
		bool m_Shutdown;

		

	};

}



