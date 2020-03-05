#include "ocpch.h"
#include "Orthographic2DCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace oc {

	Orthographic2DCamera::Orthographic2DCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Orthographic2DCamera::RecalculateViewMatrix()
	{
		// Transformation from LOCAL to WORLD coordinates : model matrix
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1)); // rotate along z axis

		m_ViewMatrix = glm::inverse(model);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

	}

}