#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

class ImGuiMenu
{
public:
	void tick();

	void setWorldPos(glm::vec3);

	static ImGuiMenu& getInstance()
	{
		static ImGuiMenu instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	}

	void setRotation(glm::vec3 rotation);
	void setScale(glm::vec3 scale);
	glm::vec3 getWorldPos();
	glm::vec3 getRotation();
	glm::vec3 getScale();

	ImGuiMenu(ImGuiMenu const&) = delete;
	void operator=(ImGuiMenu const&) = delete;

private:
	ImGuiMenu() {}

	glm::vec3 mWorldPos = glm::vec3();
	glm::vec3 mRotation = glm::vec3();
	glm::vec3 mScale = glm::vec3();
	void drawPositionProps();
	void drawRotationProps();
	void drawScaleProps();
	void drawLightProps();

};

