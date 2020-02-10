#pragma once

#include "OpsCore/Layer.h"
#include "OpsCore/Events/KeyEvent.h"
#include "OpsCore/Events/MouseEvent.h"
#include "OpsCore/Events/ApplicationEvent.h"

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
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);

		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);

		bool OnWindowResizeEvent(WindowResizeEvent& e);
		bool OnWindowCloseEvent(WindowCloseEvent& e);

	private:
		float m_Time = 0.0f;

	};

}

