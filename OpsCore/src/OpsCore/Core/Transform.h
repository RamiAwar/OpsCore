#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>


namespace oc {

	class Transform {

	public:

		Transform() :position(glm::vec3(0.0f)), rotation(glm::quat()), scale(glm::vec3(1.0f)) {};

		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

	};
}