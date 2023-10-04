#pragma once
#include <memory>
#include <Engine/Scene.h>
#include <entt/entt.hpp>

namespace ui {
	class PropertiesScreenController;
	struct ImGuiContext;
	using ToyEngine::Scene;

	class PropertiesScreen
	{
	public:
		PropertiesScreen() = default;
		PropertiesScreen(std::shared_ptr<ToyEngine::Scene> scene, ImGuiContext* context, std::shared_ptr<PropertiesScreenController> controller) :mScene(scene), mPropertiesScreenController(controller), mContext(context) {};
		void render();
	private:
		void renderObjectPropertyMenu();
		void renderCreateLightingMenu();
		void drawPositionProps();
		void drawRotationProps();
		void drawScaleProps();
		void drawCreatePointLightProps();
		void drawCreateDirectionalLightProps();

		std::string getVec3String(glm::vec3 vec);

		std::shared_ptr<PropertiesScreenController> mPropertiesScreenController;
		std::shared_ptr<ToyEngine::Scene> mScene;
		ImGuiContext* mContext;
	};


}
