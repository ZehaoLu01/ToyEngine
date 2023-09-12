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

namespace ui
{
	class PropertiesScreenController;
	class SceneHierarchyController;

	class ImGuiMenu
	{
	public:
		void tick();

		void renderHierarchyMenu();

		void renderLoggingMenu();

		void renderObjectPropertyMenu();

		static ImGuiMenu& getInstance();

		void setupControllers(std::shared_ptr<ToyEngine::MyScene> scene);

		ImGuiMenu(ImGuiMenu const&) = delete;
		void operator=(ImGuiMenu const&) = delete;
	private:
		ImGuiMenu();

		void drawPositionProps();
		void drawRotationProps();
		void drawScaleProps();
		void drawLightProps();

		std::string getVec3String(glm::vec3 vec);

		std::shared_ptr<PropertiesScreenController> mController;
		std::shared_ptr<SceneHierarchyController> mHierarchyContorller;

		std::shared_ptr<ImGui::FileBrowser> mFileBrowser = std::make_shared<ImGui::FileBrowser>();
		std::shared_ptr<FileExplorer> mFileExplorer = std::make_shared<FileExplorer>();
		std::shared_ptr<ToyEngine::MyScene> mContext;
		SceneHierarchyPanel mHierarchyPanel;
		std::vector<Controller> mScreenControllers;
	};

}
