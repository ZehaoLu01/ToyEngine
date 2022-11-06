#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

namespace ToyEngine {
	class Component;

	class GameObject
	{
	private:
		glm::vec3 mPosition;
		glm::vec3 mRotation_eular;
		glm::vec3 mScale;
		std::vector<Component> mComponents;
	public:
		glm::vec3 getPosition() const {
			return mPosition;
		}

		glm::vec3 getEularRotation() const {
			return mRotation_eular;
		}

		glm::vec3 getScale() const {
			return mScale;
		}
	};
}


