#include "UI/Model/FileExplorerModel.h"

ui::FileExplorerModel::FileExplorerModel(std::shared_ptr<ToyEngine::Scene> scene)
	:mScene(scene), ScreenModel(scene->getRegistry())
{
}
