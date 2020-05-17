#pragma once

#include "PumpkinBox/Core/Layer.h"
#include "PumpkinBox/Events/KeyEvent.h"
#include "PumpkinBox/Events/MouseEvent.h"
#include "PumpkinBox/Events/ApplicationEvent.h"

namespace pb {

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

