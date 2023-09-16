#pragma once
#include <memory>
#include <Engine/Scene.h>
#include <entt/entt.hpp>

namespace ui {
	class PropertiesScreenController;
	using ToyEngine::MyScene;

	class PropertiesScreen
	{
	public:
		PropertiesScreen() = default;
		PropertiesScreen(std::shared_ptr<ToyEngine::MyScene> scene, std::shared_ptr<PropertiesScreenController> controller) :mContext(scene), mPropertiesScreenController(controller) {};
		void render();
	private:
		void renderObjectPropertyMenu();
		void drawPositionProps();
		void drawRotationProps();
		void drawScaleProps();
		void drawLightProps();

		std::string getVec3String(glm::vec3 vec);

		std::shared_ptr<PropertiesScreenController> mPropertiesScreenController;
		std::shared_ptr<ToyEngine::MyScene> mContext;
	};


}
