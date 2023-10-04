#pragma once
#include "Engine/Scene.h"
#include <glm/gtc/type_ptr.hpp>

#include <cstring>
#include <memory>
#include <imgui.h>
#include <Engine/Component.h>
#include <UI/Controller/SceneHierarchyController.h>
namespace ui {
	struct ImGuiContext;
	class SceneHierarchyPanel
	{
		public:
			SceneHierarchyPanel() = default;
			SceneHierarchyPanel(std::shared_ptr<ToyEngine::Scene> scene) {
				SetScene(scene);
			}
			SceneHierarchyPanel(std::shared_ptr<ToyEngine::Scene> scene, ImGuiContext* context, std::shared_ptr<SceneHierarchyController> controller):mController(controller), mContext(context) {
				SetScene(scene);
			}
			SceneHierarchyPanel(std::shared_ptr<ToyEngine::Scene> scene, ImGuiContext* context, std::shared_ptr<SceneHierarchyController> controller, std::function<void(entt::entity)> onSelect);


			void render();

			entt::entity getSelectedEntity() const;

		private:
			void SetScene(const std::shared_ptr<ToyEngine::Scene> scene) {
					mScene = scene;
			}

			void hierarchyTraversal(entt::registry& registry, entt::entity head);

			void setSelected(entt::entity head);


		private:
			std::shared_ptr<ToyEngine::Scene> mScene;
			ImGuiContext* mContext;
			std::shared_ptr<SceneHierarchyController> mController;
			std::function<void(entt::entity)> mSelectEntityCallback;
	};
}
