#include "UI/Controller/PropertiesScreenController.h"

namespace ui {
	PropertiesScreenController::PropertiesScreenController(entt::registry& registry) : mRegistry(registry)
	{
		mPropertiesScreenModel = std::make_shared<PropertiesScreenModel>(registry);
	}

	void PropertiesScreenController::registerBindings()
	{
		auto weakThis = weak_from_this();

		bindVec3("properties.position", 
			[weakThis]() {
				if (auto baseSharedThis = weakThis.lock()) {
					auto sharedThis = std::dynamic_pointer_cast<PropertiesScreenController>(baseSharedThis);
					return sharedThis->mPropertiesScreenModel->getPosition();
				}
				return glm::vec3();
			}, 
			[weakThis](glm::vec3 newVal) {
				if (auto baseSharedThis = weakThis.lock()) {
					auto sharedThis = std::dynamic_pointer_cast<PropertiesScreenController>(baseSharedThis);
					sharedThis->mPropertiesScreenModel->setPosition(newVal);
				}
			}
			);

		bindVec3("properties.rotation", [weakThis]() {
			if (auto baseSharedThis = weakThis.lock()) {
				auto sharedThis = std::dynamic_pointer_cast<PropertiesScreenController>(baseSharedThis);
				return sharedThis->mPropertiesScreenModel->getRotation();
			}
			return glm::vec3();
			},
			[weakThis](glm::vec3 newVal) {
				if (auto baseSharedThis = weakThis.lock()) {
					auto sharedThis = std::dynamic_pointer_cast<PropertiesScreenController>(baseSharedThis);
					sharedThis->mPropertiesScreenModel->setRotation(newVal);
				}
			});

		bindVec3("properties.scale", [weakThis]() {
			if (auto baseSharedThis = weakThis.lock()) {
				auto sharedThis = std::dynamic_pointer_cast<PropertiesScreenController>(baseSharedThis);
				return sharedThis->mPropertiesScreenModel->getScale();
			}
			return glm::vec3();
			},
			[weakThis](glm::vec3 newVal) {
				if (auto baseSharedThis = weakThis.lock()) {
					auto sharedThis = std::dynamic_pointer_cast<PropertiesScreenController>(baseSharedThis);
					sharedThis->mPropertiesScreenModel->setScale(newVal);
				}
			});

	}
	void PropertiesScreenController::onSelectionChange(entt::entity entity)
	{
		mPropertiesScreenModel->setSelectedEntity(entity);
	}
}

