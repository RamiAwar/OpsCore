#pragma once

#include "OpsCore/Core/Layer.h"
#include "OpsCore/Events/KeyEvent.h"
#include "OpsCore/Events/MouseEvent.h"
#include "OpsCore/Events/ApplicationEvent.h"

namespace oc {

	class  ImGuiLayer: public Layer
	{
	
	public:
		ImGuiLayer(Scene* parentScene);
		~ImGuiLayer();


		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;


		void Begin();
		void End();

	private:
		float m_Time = 0.0f;

	};

}

