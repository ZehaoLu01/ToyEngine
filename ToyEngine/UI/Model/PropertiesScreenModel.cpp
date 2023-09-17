#include"UI/Model/PropertiesScreenModel.h"
#include <Engine/Scene.h>

ui::PropertiesScreenModel::PropertiesScreenModel(std::shared_ptr<ToyEngine::MyScene> scene) :mScene(scene), ScreenModel(scene->getRegistry())
{

}