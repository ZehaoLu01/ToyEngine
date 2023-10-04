#pragma once
#include "Engine/Scene.h"
#include <glm/gtc/type_ptr.hpp>

#include <cstring>
#include <memory>
#include <imgui.h>
#include <Engine/Component.h>
#include <UI/Controller/SceneHierarchyController.h>
namespace ui {
	class SceneHierarchyPanel
	{
		public:
			SceneHierarchyPanel() = default;
			SceneHierarchyPanel(std::shared_ptr<ToyEngine::Scene> context) {
				SetContext(context);
			}
			SceneHierarchyPanel(std::shared_ptr<ToyEngine::Scene> context, std::shared_ptr<SceneHierarchyController> controller):mController(controller) {
				SetContext(context);
			}
			SceneHierarchyPanel(std::shared_ptr<ToyEngine::Scene> context, std::shared_ptr<SceneHierarchyController> controller, std::function<void(entt::entity)> onSelect) :SceneHierarchyPanel(context,controller){
				mSelectEntityCallback = onSelect;
			}


			void render();

			entt::entity getSelectedEntity() const { return mSelectionContext; }

			void setSelectedEntity(entt::entity entity) {
				mSelectionContext = entity;
			}

		private:
			void SetContext(const std::shared_ptr<ToyEngine::Scene> scene) {
					mScene = scene;
			}

			void hierarchyTraversal(entt::registry& registry, entt::entity head);


		private:
			entt::entity mSelectionContext=entt::null;
			std::shared_ptr<ToyEngine::Scene> mScene;
			std::shared_ptr<SceneHierarchyController> mController;
			std::function<void(entt::entity)> mSelectEntityCallback;
	};
}
