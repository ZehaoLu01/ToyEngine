#include "UI/View/FileExplorer.h"

namespace ui {

	// constants
	static const std::string FILE_ICON_PATH = "Resources\\Images\\file.png";
	static const std::string FOLDER_ICON_PATH = "Resources\\Images\\folder.png";

	FileExplorer::FileExplorer(std::shared_ptr<FileExplorerController> controller, 
		std::shared_ptr<ToyEngine::Scene>scene):mScene(scene),mController(controller)
	{
		int width = 0;
		int height = 0;
		int channel = 0;
		mFileThumbnailTexture = std::make_shared<ToyEngine::Texture>(FILE_ICON_PATH, ToyEngine::TextureType::Diffuse, true);
		mFolderThumbnailTexture = std::make_shared<ToyEngine::Texture>(FOLDER_ICON_PATH , ToyEngine::TextureType::Diffuse, true);
	}

	void FileExplorer::render() {
		ImGui::Begin("FileExplorer");
		float widthAvail = ImGui::GetContentRegionAvail().x;

		// we need to add bracket around std::min to prevent macros expantion
		int possibleColumnNum = (std::max)((int)(widthAvail / (DEFAULT_THUMBNAIL_PADDING + DEFAULT_THUMBNAIL_WIDTH)), 1);

		if (mCurrentDirectory != mRootDirectory) {
			if (Button("<-")) {
				mCurrentDirectory = mCurrentDirectory.parent_path();
			}
		}

		ImGui::Columns(possibleColumnNum, 0, false);

		for (auto i : std::filesystem::directory_iterator(mCurrentDirectory)) {
			if (!i.is_directory()) {
				DrawFileIcon(i);
			}
			else {
				drawFolderIcon(i);
			}
			ImGui::Text(i.path().filename().string().c_str());
			ImGui::PopStyleColor();
			ImGui::NextColumn();
		}

		// We need to set columns to 1 as it will affect other other contents in the window.
		ImGui::Columns(1);

		ImGui::End();
	}
	void FileExplorer::drawFolderIcon(std::filesystem::directory_entry& i)
	{
		GLuint index = mFolderThumbnailTexture->getTextureIndex();
		ImGui::PushStyleColor(ImGuiCol_Button, FILE_BACKGROUND_COLOR);
		if (ImageButton(i.path().string().c_str(), (void*)(intptr_t)index, 
			{ DEFAULT_THUMBNAIL_WIDTH ,DEFAULT_THUMBNAIL_WIDTH }, { 0, 1 }, { 1, 0 }, { 1.0f, 1.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f })) {
			mCurrentDirectory = i.path();
			render();
		}
	}
	void FileExplorer::DrawFileIcon(std::filesystem::directory_entry& i)
	{
		GLuint index = mFileThumbnailTexture->getTextureIndex();
		//https://github.com/ocornut/imgui/issues/4216
		ImGui::PushStyleColor(ImGuiCol_Button, FILE_BACKGROUND_COLOR);
		if (ImageButton(i.path().string().c_str(), (void*)(intptr_t)index, 
			{ DEFAULT_THUMBNAIL_WIDTH ,DEFAULT_THUMBNAIL_WIDTH }, { 0, 1 }, { 1, 0 }, { 1.0f, 1.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f })) {
			ViewEvent event(mScene->getRegistry());

			//TODO: query name from user
			event.name = "onModelFileButtonDown";
			event.value = "ModelRoot";
			event.path = i.path().string();
			event.viewEventType = ViewEventType::ButtonEvent;
			event.parentEntity = mScene->getRootEntity();
			mController->addViewEvent(event);
		}
	}
}

