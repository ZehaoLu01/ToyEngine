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

using ImGui::Button;
using ImGui::ImageButton;
#ifndef test
#define test

#endif // !1


namespace ui {
	class FileExplorer {
		const float DEFAULT_THUMBNAIL_WIDTH = 128;
		const float DEFAULT_THUMBNAIL_PADDING = 30;
	public:
		FileExplorer();

		void render();

	private:
		const ImVec4 FILE_BACKGROUND_COLOR = ImVec4(1.f, 1.f, 1.f, 0.6f);
		const std::filesystem::path mRootDirectory = std::filesystem::path("Include");
		std::filesystem::path mCurrentDirectory = mRootDirectory;

		std::shared_ptr<ToyEngine::Texture> mFolderThumbnailTexture;
		std::shared_ptr<ToyEngine::Texture> mFileThumbnailTexture;

		unsigned char* mFileThumbnail;
	};

}