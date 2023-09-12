#pragma once
#include "Engine/Scene.h"
#include <glm/gtc/type_ptr.hpp>

#include <cstring>
#include <memory>
#include <imgui.h>
#include <Engine/Component.h>
#include <imgui_internal.h>
#include <UI/Controller/SceneHierarchyController.h>
namespace ui {
	class SceneHierarchyPanel
	{
		public:
			SceneHierarchyPanel() = default;
			SceneHierarchyPanel(std::shared_ptr<ToyEngine::MyScene> context) {
				SetContext(context);
			}
			SceneHierarchyPanel(std::shared_ptr<ToyEngine::MyScene> context, std::shared_ptr<SceneHierarchyController> controller):mController(controller) {
				SetContext(context);
			}


			void tick();

			entt::entity getSelectedEntity() const { return mSelectionContext; }

			void SetSelectedEntity(entt::entity entity) {
				mSelectionContext = entity;
			}
		private:
			void SetContext(const std::shared_ptr<ToyEngine::MyScene> scene) {
					mScene = scene;
			}

		private:
			entt::entity mSelectionContext=entt::null;
			std::shared_ptr<ToyEngine::MyScene> mScene;
			std::shared_ptr<SceneHierarchyController> mController;
	};
}
