#pragma once

#include "PumpkinBox/Renderer/Cameras/OrthographicCamera.h"
#include "PumpkinBox/Core/Timestep.h"

#include "PumpkinBox/Events/MouseEvent.h"
#include "PumpkinBox/Events/ApplicationEvent.h"

namespace pb {

	class OrthographicCameraController {

	public:

		OrthographicCameraController(float aspectRatio, bool movementEnabled = false, bool scrollEnabled=false, bool rotationEnabled = false); // aspect ratio * 2 units of space no matter screen res

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:

		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		
		OrthographicCamera m_Camera;

		bool m_RotationEnabled;
		bool m_MovementEnabled;
		bool m_ScrollEnabled;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 1.0f, m_CameraRotationSpeed = 60.0f;


		

	};
}