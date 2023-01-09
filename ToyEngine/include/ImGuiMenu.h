#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ImGuiMenu
{
public:
	static void tick();

	static void setWorldPos(glm::vec3);

	static void setRotation(glm::vec3 rotation);
	static void setScale(glm::vec3 scale);
	static glm::vec3 getWorldPos();
	static glm::vec3 getRotation();
	static glm::vec3 getScale();

private:
	static glm::vec3 mWorldPos;
	static glm::vec3 mRotation;
	static glm::vec3 mScale;

};

