#include"UI/Model/PropertiesScreenModel.h"
#include <Engine/Scene.h>

ui::PropertiesScreenModel::PropertiesScreenModel(std::shared_ptr<ToyEngine::Scene> scene) :mScene(scene), ScreenModel(scene->getRegistry())
{

}