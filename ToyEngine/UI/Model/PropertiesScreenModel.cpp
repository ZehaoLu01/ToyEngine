#include"UI/Model/InspectorPanelModel.h"
#include <Engine/Scene.h>

ui::InspectorPanelModel::InspectorPanelModel(std::shared_ptr<ToyEngine::Scene> scene) :mScene(scene), ScreenModel(scene->getRegistry())
{

}