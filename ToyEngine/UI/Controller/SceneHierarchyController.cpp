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

	void SceneHierarchyController::registerBindings() {
		auto weakThis = weak_from_this();

		bindButtonInteractHandler("onDeleteEnittyButtonDown", [weakThis](const ViewEvent& event) {
			if (auto baseSharedThis = weakThis.lock()) {
				auto sharedThis = std::dynamic_pointer_cast<SceneHierarchyController>(baseSharedThis);

				entt::entity selected = static_cast<entt::entity>(stoi(event.value));
				auto relation = event.registry.get<ToyEngine::RelationComponent>(selected);

				if (selected != entt::null) {
					sharedThis->destroyEntityRecursively(selected);

					if (relation.parent != entt::null && event.registry.valid(relation.parent)) {
						auto parentRelation = event.registry.try_get<ToyEngine::RelationComponent>(relation.parent);
						if (!parentRelation) {
							ToyEngine::Logger::DEBUG_WARNING("Parent relation component is not found.");
							return;
						}
						
						auto iter = parentRelation->children.begin();
						while (iter != parentRelation->children.end()) {
							if (*iter == selected) {
								parentRelation->children.erase(iter);
								return;
							}
							else {
								iter++;
							}
						}
						ToyEngine::Logger::DEBUG_WARNING("Selected entity not found in parent relation component!");
					}
				}
			}
			});
	}

	void SceneHierarchyController::destroyEntityRecursively(entt::entity entity) {
		if (entity == entt::null) {
			return;
		}
		const auto relation = mRegistry.try_get<ToyEngine::RelationComponent>(entity);
		if (!relation) {
			ToyEngine::Logger::DEBUG_ERROR("No Relation component");
			return;
		}
		for (const auto& child : relation->children) {
			destroyEntityRecursively(child);
		}

		auto tag = mRegistry.try_get<ToyEngine::TagComponent>(entity);
		if (tag) {
			ToyEngine::Logger::DEBUG_INFO("Recursively destroyed " + tag->name);
		}
		else {
			ToyEngine::Logger::DEBUG_INFO("Recursively destroyed an entity without a tag");
		}
		mRegistry.destroy(entity);
	}

	//TODO Remove this?
	void SceneHierarchyController::onSelectionChange(entt::entity entity)
	{
		std::cout << "SceneHierarchyController select entity: " << mRegistry.get<ToyEngine::TagComponent>(entity).name << std::endl;
		mSceneHierarchyModel->setSelectedEntity(entity);
	}
}


