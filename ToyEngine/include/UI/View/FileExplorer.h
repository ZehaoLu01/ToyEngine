#pragma once
#include <imgui.h>
#include <filesystem>
#include <string>
#include "Resource/StbImageLoader.h"
#include <algorithm>
#include <Resource/Texture.h>
#include <memory>
#include <glad/glad.h>
#include "Resource/Texture.h"
#include "Resource/stb_image.h"
#include <UI/Controller/FileExplorerController.h>
#include <Engine/Scene.h>

using ImGui::Button;
using ImGui::ImageButton;
#ifndef test
#define test

#endif // !1


namespace ui {
	const float DEFAULT_THUMBNAIL_WIDTH = 128;
	const float DEFAULT_THUMBNAIL_PADDING = 30;
	
	class FileExplorer {
	public:
		FileExplorer(std::shared_ptr<FileExplorerController> controller, std::shared_ptr<ToyEngine::MyScene> scene);
		FileExplorer()=default;
		FileExplorer(const FileExplorer& explorer) = default;
		FileExplorer& operator=(const FileExplorer&) = default;

		void render();

		void drawFolderIcon(std::filesystem::directory_entry& i);

		void DrawFileIcon(std::filesystem::directory_entry& i);

	private:
		ImVec4 FILE_BACKGROUND_COLOR = ImVec4(1.f, 1.f, 1.f, 0.6f);
		std::filesystem::path mRootDirectory = std::filesystem::path("Resources");
		std::filesystem::path mCurrentDirectory = mRootDirectory;

		std::shared_ptr<ToyEngine::Texture> mFolderThumbnailTexture;
		std::shared_ptr<ToyEngine::Texture> mFileThumbnailTexture;

		unsigned char* mFileThumbnail;
		std::shared_ptr<FileExplorerController> mController;

		std::shared_ptr<ToyEngine::MyScene> mScene;
	};

}