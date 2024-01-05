#pragma once
#include "UI/Model/ScreenModel.h"
#include "Engine/Scene.h"

namespace ui {
	class FileExplorerModel :
		public ScreenModel, public std::enable_shared_from_this<FileExplorerModel>
	{
	public:
		FileExplorerModel(std::shared_ptr<ToyEngine::Scene> scene);
		auto getCurrentScene() {
			return mScene;
		}
		
	private:
		std::shared_ptr<ToyEngine::Scene> mScene;
	};

}