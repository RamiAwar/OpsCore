#pragma once

#include "OpsCore/Core/Layer.h"
#include "OpsCore/Events/KeyEvent.h"
#include "OpsCore/Events/MouseEvent.h"
#include "OpsCore/Events/ApplicationEvent.h"

namespace oc {

	class  ImGuiLayer: public Layer
	{
	
	public:
		ImGuiLayer();
		~ImGuiLayer();

		static void Init();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;


		void Begin();
		void End();

		static void Shutdown();

	private:
		float m_Time = 0.0f;

	};

}

