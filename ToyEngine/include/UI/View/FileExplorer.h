#pragma once
#include <imgui.h>
#include <filesystem>
#include <string>
#include "Resource/StbImageLoader.h"
#include <algorithm>

using ImGui::Button;
using ImGui::ImageButton;


namespace ui {
	class FileExplorer {
	public:
		FileExplorer() {
			int width = 0;
			int height = 0;
			int channel = 0;
			mFolderThumbnail = ToyEngine::StbImageLoader::getImageFrom("folder.png",&width, &height, &channel);
			mFileThumbnail = ToyEngine::StbImageLoader::getImageFrom("file.png", &width, &height, &channel);
		}

		void render() {
			ImGui::Begin("FileExplorer");

			const float defaultThumbnailWidth = 128;
			const float defaultPadding = 30;
			float widthAvail = ImGui::GetContentRegionAvail().x;

			// we need to add bracket around std::min to prevent macros expantion
			int possibleColumnNum = (std::max)((int)(widthAvail / (defaultPadding + defaultThumbnailWidth)), 1);

			if (mCurrentDirectory != mRootDirectory) {
				if (Button("<-")) {
					mCurrentDirectory = mCurrentDirectory.parent_path();
				}
			}

			ImGui::Columns(possibleColumnNum);

			for (auto i : std::filesystem::directory_iterator(mCurrentDirectory)) {
				if (!i.is_directory()) {
					if (Button(i.path().string().c_str())) {

					}
				}
				else {
					if (Button(i.path().string().c_str())) {
						mCurrentDirectory = i.path();
						render();
					}
				}
				ImGui::NextColumn();
			}
			
			// We need to set columns to 1 as it will affect other other contents in the window.
			ImGui::Columns(1);

			ImGui::End();
		}


	private:
		const std::filesystem::path mRootDirectory = std::filesystem::path("Include");
		std::filesystem::path mCurrentDirectory = mRootDirectory;

		unsigned char* mFolderThumbnail;
		unsigned char* mFileThumbnail;
	};

}