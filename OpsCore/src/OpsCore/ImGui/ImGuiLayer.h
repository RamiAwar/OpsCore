#pragma once

#include "OpsCore/Layer.h"

namespace oc {

	class OPSCORE_API ImGuiLayer: public Layer
	{
	
	public:
		ImGuiLayer();
		~ImGuiLayer();


		void OnAttach();
		void OnDetach();
		void OnUpdate();

		void OnEvent(Event& event);

	private:
		float m_Time = 0.0f;

	};

}

