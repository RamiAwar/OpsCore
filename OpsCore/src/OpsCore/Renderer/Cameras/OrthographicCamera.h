#pragma once

#include <glm/glm.hpp>


/*
	Coordinate systems, cameras:
	For reference, read this : https://learnopengl.com/Getting-started/Coordinate-Systems

	Orthographic projection
	An orthographic projection matrix defines a cube-like frustum box that defines the clipping space 
	where each vertex outside this box is clipped. When creating an orthographic projection matrix we 
	specify the width, height and length of the visible frustum. All the coordinates inside this frustum 
	will end up within the NDC range after transformed by its matrix and thus won't be clipped.
*/

namespace oc {

	class OrthographicCamera {

	public:

		OrthographicCamera(float left, float right, float bottom, float top);
		void SetProjection(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return m_Position; }
		float GetRotation() const { return m_RotationEnabled; }

		void SetPosition(const glm::vec3 position) { m_Position = position; RecalculateViewMatrix(); }
		void SetRotation(float rotation) { m_RotationEnabled = rotation; RecalculateViewMatrix(); } // basically a z rotation (2d)
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:

		void RecalculateViewMatrix();
	
	private:

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_RotationEnabled = 0.0f;
	};
}