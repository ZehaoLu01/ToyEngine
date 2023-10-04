#include "UI/Controller/PropertiesScreenController.h"
#include "Renderer/RenderSystem.h"
namespace ui {
	PropertiesScreenController::PropertiesScreenController(std::unique_ptr<PropertiesScreenModel>&& model): mPropertiesScreenModel(std::move(model)), mRegistry(mPropertiesScreenModel->getRegistry())
	{
		
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

		bindVec3("properties.rotation", 
			[weakThis]() {
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

		bindVec3("properties.scale", 
			[weakThis]() 
			{
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

		bindButtonInteractHandler("onCreatePointLightButtonDown", [weakThis](const ViewEvent& event) {
			if (auto baseSharedThis = weakThis.lock()) {
				auto sharedThis = std::dynamic_pointer_cast<PropertiesScreenController>(baseSharedThis);
				// TODO: improve this.
				auto& vectors = event.vectorGroup;
				auto& floats = event.floatGroup;
				if (vectors.empty()) {	
					sharedThis->mPropertiesScreenModel->addPointLight();
				}

				if (vectors.size() < 4 || floats.size() < 3) {
					std::cerr << "Create Point light Button invalid event arguments." << std::endl;
				}

				sharedThis->mPropertiesScreenModel->addPointLight(vectors[0], vectors[1], vectors[2], vectors[3], floats[0], floats[1], floats[2]);
			}
		});

		bindButtonInteractHandler("onCreateDirctionalLightButtonDown", [weakThis](const ViewEvent& event) {
			if (auto baseSharedThis = weakThis.lock()) {
				auto sharedThis = std::dynamic_pointer_cast<PropertiesScreenController>(baseSharedThis);
				// TODO: improve this.
				auto& vectors = event.vectorGroup;
				auto& floats = event.floatGroup;
				if (vectors.empty()) {
					sharedThis->mPropertiesScreenModel->addPointLight();
				}

				if (vectors.size() < 4 || floats.size() < 3) {
					ToyEngine::Logger::DEBUG_ERROR("Create Light Cube Button invalid event arguments.");
				}

				sharedThis->mPropertiesScreenModel->addDirectionalLight(vectors[0], vectors[1], vectors[2], vectors[3], floats[0], floats[1], floats[2]);
			}
			});
	}
	void PropertiesScreenController::onSelectionChange(entt::entity entity)
	{
		mPropertiesScreenModel->setSelectedEntity(entity);
	}
}

