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
		const float defaultThumbnailWidth = 128;
		const float defaultPadding = 30;
	public:
		FileExplorer() {
			int width = 0;
			int height = 0;
			int channel = 0;
			auto fileThumbnail = ToyEngine::StbImageLoader::getImageFrom("file.png",&width, &height, &channel);
			mFileThumbnailTexture = std::make_shared<ToyEngine::Texture>(fileThumbnail, width, height, GL_RGBA, GL_RGBA, 0, ToyEngine::TextureType::Diffuse);

			auto folderThumbnail = ToyEngine::StbImageLoader::getImageFrom("folder.png", &width, &height, &channel);
			mFolderThumbnailTexture = std::make_shared<ToyEngine::Texture>(folderThumbnail, width, height, GL_RGBA, GL_RGBA, 0, ToyEngine::TextureType::Diffuse);
		}

		void render() {
			ImGui::Begin("FileExplorer");
			float widthAvail = ImGui::GetContentRegionAvail().x;

			// we need to add bracket around std::min to prevent macros expantion
			int possibleColumnNum = (std::max)((int)(widthAvail / (defaultPadding + defaultThumbnailWidth)), 1);

			if (mCurrentDirectory != mRootDirectory) {
				if (Button("<-")) {
					mCurrentDirectory = mCurrentDirectory.parent_path();
				}
			}

			ImGui::Columns(possibleColumnNum, 0, false);

			for (auto i : std::filesystem::directory_iterator(mCurrentDirectory)) {
				if (!i.is_directory()) {
					GLuint index = mFileThumbnailTexture->getTextureIndex();
					//https://github.com/ocornut/imgui/issues/4216
					ImGui::PushStyleColor(ImGuiCol_Button, FILE_BACKGROUND_COLOR);
					if (ImageButton(i.path().string().c_str(), (void*)(intptr_t)index, { defaultThumbnailWidth ,defaultThumbnailWidth }, { 0, 1 }, { 1, 0 }, { 1.0f, 1.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f })) {
					}
					ImGui::Text(i.path().filename().string().c_str());
					ImGui::PopStyleColor();
				}
				else {
					GLuint index = mFolderThumbnailTexture->getTextureIndex();
					ImGui::PushStyleColor(ImGuiCol_Button, FILE_BACKGROUND_COLOR);
					if (ImageButton(i.path().string().c_str(), (void*)(intptr_t)index, { defaultThumbnailWidth ,defaultThumbnailWidth }, {0, 1}, {1, 0}, {1.0f, 1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f})) {
						mCurrentDirectory = i.path();
						render();
					}
					ImGui::Text(i.path().filename().string().c_str());
					ImGui::PopStyleColor();
				}
				ImGui::NextColumn();
			}
			
			// We need to set columns to 1 as it will affect other other contents in the window.
			ImGui::Columns(1);

			ImGui::End();
		}


	private:
		const ImVec4 FILE_BACKGROUND_COLOR = ImVec4(1.f, 1.f, 1.f, 0.6f);
		const std::filesystem::path mRootDirectory = std::filesystem::path("Include");
		std::filesystem::path mCurrentDirectory = mRootDirectory;

		std::shared_ptr<ToyEngine::Texture> mFolderThumbnailTexture;
		std::shared_ptr<ToyEngine::Texture> mFileThumbnailTexture;

		unsigned char* mFileThumbnail;
	};

}