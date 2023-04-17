#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <string>
#include "../../../submodule/FileExplorer/imfilebrowser.h"
#include "UI/View/FileExplorer.h"



namespace ui
{
	class PropertiesScreenController;

	class ImGuiMenu
	{
	public:
		void tick();

		void renderHierarchyMenu();

		void renderLoggingMenu();

		void renderObjectPropertyMenu();

		static ImGuiMenu& getInstance()
		{
			static ImGuiMenu instance; // Guaranteed to be destroyed.
			// Instantiated on first use.
			return instance;
		}

		void setController(std::shared_ptr<PropertiesScreenController> controller);

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
		std::shared_ptr<ImGui::FileBrowser> mFileBrowser = std::make_shared<ImGui::FileBrowser>();
		std::shared_ptr<FileExplorer> mFileExplorer = std::make_shared<FileExplorer>();

	};

}
