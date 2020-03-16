#pragma once

#include "OpsCore/Core/Core.h"

#include "OpsCore/Core/LayerStack.h"
#include "OpsCore/Events/Event.h"
#include "OpsCore/ImGui/ImGuiLayer.h"

#include "OpsCore/Core/Timestep.h"

namespace oc {

	class Scene
	{

	public:

		Scene();
		virtual ~Scene();

		void OnEvent(Event& e);

		// TODO: Change boolean minimized to a struct representing various window properties
		void Update(oc::Timestep ts, bool minimized);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:

		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

	};

}



