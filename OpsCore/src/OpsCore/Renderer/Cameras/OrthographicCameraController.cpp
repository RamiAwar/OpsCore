#include "ocpch.h"
#include "OrthographicCameraController.h"
#include "OpsCore/Core/Input.h"
#include "OpsCore/Core/KeyCodes.h"

oc::OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool scrollEnabled, bool movementEnabled, bool rotationEnabled)
	: m_AspectRatio(aspectRatio), 
	  m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
	  m_RotationEnabled(rotationEnabled),
	  m_MovementEnabled(movementEnabled),
	  m_ScrollEnabled(scrollEnabled)
{
}

void oc::OrthographicCameraController::OnUpdate(Timestep ts)
{
	if (m_MovementEnabled) {
		if (oc::Input::IsKeyPressed(OC_KEY_A)) { m_CameraPosition.x -= m_CameraTranslationSpeed * ts; }
		else if (oc::Input::IsKeyPressed(OC_KEY_D)) { m_CameraPosition.x += m_CameraTranslationSpeed * ts; }

		if (oc::Input::IsKeyPressed(OC_KEY_W)) { m_CameraPosition.y += m_CameraTranslationSpeed * ts; }
		else if (oc::Input::IsKeyPressed(OC_KEY_S)) { m_CameraPosition.y -= m_CameraTranslationSpeed * ts; }
	}

	if (m_RotationEnabled) {
		if (oc::Input::IsKeyPressed(OC_KEY_Q)) { m_CameraRotation += m_CameraRotationSpeed * ts; }
		else if (oc::Input::IsKeyPressed(OC_KEY_E)) { m_CameraRotation -= m_CameraRotationSpeed * ts; }
	}

	m_Camera.SetRotation(m_CameraRotation);
	m_Camera.SetPosition(m_CameraPosition);
	m_CameraTranslationSpeed = 1.5*m_ZoomLevel;
}

void oc::OrthographicCameraController::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseScrolledEvent>(OC_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
	dispatcher.Dispatch<WindowResizeEvent>(OC_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
}

bool oc::OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
{
	if (m_ScrollEnabled) {
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
	}
	
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return true;
}

bool oc::OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
{
	m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return true;
}
