#include "pbpch.h"
#include "OrthographicCameraController.h"
#include "PumpkinBox/Core/Input.h"
#include "PumpkinBox/Core/KeyCodes.h"

pb::OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool scrollEnabled, bool movementEnabled, bool rotationEnabled)
	: m_AspectRatio(aspectRatio), 
	  m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
	  m_RotationEnabled(rotationEnabled),
	  m_MovementEnabled(movementEnabled),
	  m_ScrollEnabled(scrollEnabled)
{
}

void pb::OrthographicCameraController::OnUpdate(Timestep ts)
{
	if (m_MovementEnabled) {
		if (pb::Input::IsKeyPressed(PB_KEY_A)) { m_CameraPosition.x -= m_CameraTranslationSpeed * ts; }
		else if (pb::Input::IsKeyPressed(PB_KEY_D)) { m_CameraPosition.x += m_CameraTranslationSpeed * ts; }

		if (pb::Input::IsKeyPressed(PB_KEY_W)) { m_CameraPosition.y += m_CameraTranslationSpeed * ts; }
		else if (pb::Input::IsKeyPressed(PB_KEY_S)) { m_CameraPosition.y -= m_CameraTranslationSpeed * ts; }
	}

	if (m_RotationEnabled) {
		if (pb::Input::IsKeyPressed(PB_KEY_Q)) { m_CameraRotation += m_CameraRotationSpeed * ts; }
		else if (pb::Input::IsKeyPressed(PB_KEY_E)) { m_CameraRotation -= m_CameraRotationSpeed * ts; }
	}

	m_Camera.SetRotation(m_CameraRotation);
	m_Camera.SetPosition(m_CameraPosition);
	m_CameraTranslationSpeed = 1.5*m_ZoomLevel;
}

void pb::OrthographicCameraController::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseScrolledEvent>(PB_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
	dispatcher.Dispatch<WindowResizeEvent>(PB_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
}

bool pb::OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
{
	if (m_ScrollEnabled) {
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
	}
	
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return true;
}

bool pb::OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
{
	m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return true;
}
