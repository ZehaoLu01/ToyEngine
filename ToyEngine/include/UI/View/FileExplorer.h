#pragma once
#include <imgui.h>
#include <filesystem>
#include <string>

namespace ui {
	class FileExplorer {
	public:
		void render() {
			ImGui::Begin("FileExplorer");

			if (mCurrentDirectory != mRootDirectory) {
				if (ImGui::Button("<-")) {
					mCurrentDirectory = mCurrentDirectory.parent_path();
				}
			}

			for (auto i : std::filesystem::directory_iterator(mCurrentDirectory)) {
				if (!i.is_directory()) {
					ImGui::Button(i.path().string().c_str());
				}
				else {
					if (ImGui::Button(i.path().string().c_str())) {
						mCurrentDirectory = i.path();
						render();
					}
				}
			}

			ImGui::End();
		}


	private:
		const std::filesystem::path mRootDirectory = std::filesystem::path("Include");
		std::filesystem::path mCurrentDirectory = mRootDirectory;
	};

}