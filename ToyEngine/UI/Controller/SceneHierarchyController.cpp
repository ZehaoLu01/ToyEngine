#include <UI/Controller/SceneHierarchyController.h>
#include <iostream>
namespace ui {
	SceneHierarchyController::SceneHierarchyController(entt::registry& registry): mRegistry(registry),mSceneHierarchyModel(std::make_shared<SceneHierarchyModel>(registry))
	{
	
	};

	std::vector<std::string> SceneHierarchyController::getTagNames()
	{
		return mSceneHierarchyModel->getTagNames();
	}
	void SceneHierarchyController::onSelectionChange(entt::entity entity)
	{
		std::cout << "SceneHierarchyController select entity: " << mRegistry.get<ToyEngine::TagComponent>(entity).name << std::endl;
		mSceneHierarchyModel->setSelectedEntity(entity);
	}
}


