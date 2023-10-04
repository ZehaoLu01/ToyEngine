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

	struct ImGuiContext {
		entt::entity selectedEntity = entt::null;
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
		PropertiesScreen mPropertiesScreen;

		ImGuiContext mContext;
		std::shared_ptr<ToyEngine::Scene> mScene;
		std::vector<std::shared_ptr<Controller>> mScreenControllers;
	};

}
