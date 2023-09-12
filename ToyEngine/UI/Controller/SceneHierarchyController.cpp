#include <UI/Controller/SceneHierarchyController.h>

namespace ui {
	SceneHierarchyController::SceneHierarchyController(entt::registry& registry): mRegistry(registry)
	{
	};

	std::vector<std::string> SceneHierarchyController::getTagNames()
	{
		return mSceneHierarchyModel->getTagNames();
	}
}


