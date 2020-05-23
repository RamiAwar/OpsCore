#pragma once
#include "PumpkinBox/Core/Core.h"
#include "PumpkinBox/Core/Log.h"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace pb {

	class Quaternion {
	public:

		Quaternion(): m_Quaternion(glm::quat()) 
		{ 
			m_Components = { m_Quaternion.x, m_Quaternion.y, m_Quaternion.z, m_Quaternion.w }; 
		}
		
		Quaternion(const glm::vec3& uvw) : m_Quaternion(glm::quat(uvw)) 
		{
			m_Components = { m_Quaternion.x, m_Quaternion.y, m_Quaternion.z, m_Quaternion.w };
		};
		
		Quaternion(const glm::vec4& xyzw) : m_Quaternion(glm::quat(xyzw)), m_Components(xyzw) {}
		~Quaternion() {}

		static Quaternion Identity;
		
		glm::vec3 eulerAngles;
		Quaternion normalized();






		float& Quaternion::operator[](int);

	private:

		glm::quat m_Quaternion;
		glm::vec4 m_Components;
	};
}