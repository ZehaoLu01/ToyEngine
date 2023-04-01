#include "UI/Controller/PropertiesScreenController.h"

namespace ui {
	PropertiesScreenController::PropertiesScreenController()
	{
		mPropertiesScreenModel = std::make_shared<PropertiesScreenModel>();
	}

	PropertiesScreenController::PropertiesScreenController(std::vector<std::shared_ptr<ToyEngine::RenderComponent>> selectedComponents)
	{
		mPropertiesScreenModel = std::make_shared<PropertiesScreenModel>(selectedComponents);
	}


	void PropertiesScreenController::registerBindings()
	{
		auto weakThis = weak_from_this();

		bindVec3("properties.position", 
			[weakThis]() {
				if (auto sharedThis = weakThis.lock()) {
					return sharedThis->mPropertiesScreenModel->getPosition();
				}
				return glm::vec3();
			}, 
			[weakThis](glm::vec3 newVal) {
				if (auto sharedThis = weakThis.lock()) {
					sharedThis->mPropertiesScreenModel->setPosition(newVal);
				}
			}
			);

		bindVec3("properties.rotation", [weakThis]() {
			if (auto sharedThis = weakThis.lock()) {
				return sharedThis->mPropertiesScreenModel->getRotation();
			}
			return glm::vec3();
			},
			[weakThis](glm::vec3 newVal) {
				if (auto sharedThis = weakThis.lock()) {
					sharedThis->mPropertiesScreenModel->setRotation(newVal);
				}
			});

		bindVec3("properties.scale", [weakThis]() {
			if (auto sharedThis = weakThis.lock()) {
				return sharedThis->mPropertiesScreenModel->getScale();
			}
			return glm::vec3();
			},
			[weakThis](glm::vec3 newVal) {
				if (auto sharedThis = weakThis.lock()) {
					sharedThis->mPropertiesScreenModel->setScale(newVal);
				}
			});

	}
}

