#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <string>
#include "../../../submodule/FileExplorer/imfilebrowser.h"
#include "UI/View/FileExplorer.h"
#include <Engine/Scene.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <sstream>
#include <UI/Controller/PropertiesScreenController.h>
#include <UI/View/SceneHierarchyPanel.h>
#include "PropertiesScreen.h"

namespace ui
{
	class PropertiesScreenController;
	class SceneHierarchyController;

	class ImGuiContext {
	public:
		void setSelectedEntity(entt::entity entity) {
			std::string name;

			if (entity == entt::null) {
				name = "null";
			}
			else if(mScene){
				name = mScene->getRegistry().get<ToyEngine::TagComponent>(entity).name;
			}
			else {
				ToyEngine::Logger::DEBUG_ERROR("ImGuiContext is not initailized using scene");
				return;
			}
			ToyEngine::Logger::DEBUG_INFO("Selected " + name);

			mSelectedEntity = entity;
		}

		entt::entity getSelectedEntity() {
			return mSelectedEntity;
		}

		void setScene(std::shared_ptr<Scene>scene ) {
			mScene = scene;
		}

	private:
		entt::entity mSelectedEntity = entt::null;
		std::shared_ptr<Scene> mScene;
	};

	class ImGuiManager
	{
	public:
		void tick();

		void renderLoggingMenu();

		static ImGuiManager& getInstance();

		void setupControllers(std::shared_ptr<ToyEngine::Scene> scene);

		ImGuiManager(ImGuiManager const&) = delete;
		void operator=(ImGuiManager const&) = delete;
	private:
		ImGuiManager();

		std::shared_ptr<PropertiesScreenController> mPropertiesScreenController;
		std::shared_ptr<SceneHierarchyController> mHierarchyContorller;
		std::shared_ptr<FileExplorerController> mFileExplorerController;

		std::shared_ptr<ImGui::FileBrowser> mFileBrowser;
		FileExplorer mFileExplorer;
		SceneHierarchyPanel mHierarchyPanel;
		InspectorScreen mPropertiesScreen;

		ImGuiContext mContext;
		std::shared_ptr<ToyEngine::Scene> mScene;
		std::vector<std::shared_ptr<Controller>> mScreenControllers;
	};

}
