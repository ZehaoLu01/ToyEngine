#include <UI/Controller/SceneHierarchyController.h>
#include <iostream>
namespace ui {
	SceneHierarchyController::SceneHierarchyController(std::unique_ptr<ui::SceneHierarchyModel>&& model):mSceneHierarchyModel(std::move(model)), mRegistry(mSceneHierarchyModel->getRegistry())
	{
	
	};

	std::vector<std::string> SceneHierarchyController::getTagNames()
	{
		return mSceneHierarchyModel->getTagNames();
	}

	//TODO Remove this?
	void SceneHierarchyController::onSelectionChange(entt::entity entity)
	{
		std::cout << "SceneHierarchyController select entity: " << mRegistry.get<ToyEngine::TagComponent>(entity).name << std::endl;
		mSceneHierarchyModel->setSelectedEntity(entity);
	}
}


