#include "UI/Controller/InspectorPanelController.h"
#include "Renderer/RenderSystem.h"
namespace ui {
	InspectorPanelController::InspectorPanelController(std::unique_ptr<InspectorPanelModel>&& model): mInspectorPanelModel(std::move(model)), mRegistry(mInspectorPanelModel->getRegistry())
	{
		
	}

	void InspectorPanelController::registerBindings()
	{
		auto weakThis = weak_from_this();

		bindVec3("properties.position", 
			[weakThis]() {
				if (auto baseSharedThis = weakThis.lock()) {
					auto sharedThis = std::dynamic_pointer_cast<InspectorPanelController>(baseSharedThis);
					return sharedThis->mInspectorPanelModel->getPosition();
				}
				return glm::vec3();
			}, 
			[weakThis](glm::vec3 newVal) {
				if (auto baseSharedThis = weakThis.lock()) {
					auto sharedThis = std::dynamic_pointer_cast<InspectorPanelController>(baseSharedThis);
					sharedThis->mInspectorPanelModel->setPosition(newVal);
				}
			}
		);

		bindVec3("properties.rotation", 
			[weakThis]() {
			if (auto baseSharedThis = weakThis.lock()) {
				auto sharedThis = std::dynamic_pointer_cast<InspectorPanelController>(baseSharedThis);
				return sharedThis->mInspectorPanelModel->getRotation();
			}
			return glm::vec3();
			},
			[weakThis](glm::vec3 newVal) {
				if (auto baseSharedThis = weakThis.lock()) {
					auto sharedThis = std::dynamic_pointer_cast<InspectorPanelController>(baseSharedThis);
					sharedThis->mInspectorPanelModel->setRotation(newVal);
				}
			});

		bindVec3("properties.scale", 
			[weakThis]() 
			{
			if (auto baseSharedThis = weakThis.lock()) {
				auto sharedThis = std::dynamic_pointer_cast<InspectorPanelController>(baseSharedThis);
				return sharedThis->mInspectorPanelModel->getScale();
			}
			return glm::vec3();
			},
			[weakThis](glm::vec3 newVal) {
				if (auto baseSharedThis = weakThis.lock()) {
					auto sharedThis = std::dynamic_pointer_cast<InspectorPanelController>(baseSharedThis);
					sharedThis->mInspectorPanelModel->setScale(newVal);
				}
			});

		bindButtonInteractHandler("onCreatePointLightButtonDown", [weakThis](const ViewEvent& event) {
			if (auto baseSharedThis = weakThis.lock()) {
				auto sharedThis = std::dynamic_pointer_cast<InspectorPanelController>(baseSharedThis);
				// TODO: improve this.
				auto& vectors = event.vectorGroup;
				auto& floats = event.floatGroup;
				if (vectors.empty()) {	
					sharedThis->mInspectorPanelModel->addPointLight();
				}

				if (vectors.size() < 4 || floats.size() < 3) {
					std::cerr << "Create Point light Button invalid event arguments." << std::endl;
				}

				sharedThis->mInspectorPanelModel->addPointLight(vectors[0], vectors[1], vectors[2], vectors[3], floats[0], floats[1], floats[2]);
			}
		});

		bindButtonInteractHandler("onCreateDirctionalLightButtonDown", [weakThis](const ViewEvent& event) {
			if (auto baseSharedThis = weakThis.lock()) {
				auto sharedThis = std::dynamic_pointer_cast<InspectorPanelController>(baseSharedThis);
				// TODO: improve this.
				auto& vectors = event.vectorGroup;
				auto& floats = event.floatGroup;
				if (vectors.empty()) {
					sharedThis->mInspectorPanelModel->addPointLight();
				}

				if (vectors.size() < 4 || floats.size() < 3) {
					ToyEngine::Logger::DEBUG_ERROR("Create Light Cube Button invalid event arguments.");
				}

				sharedThis->mInspectorPanelModel->addDirectionalLight(vectors[0], vectors[1], vectors[2], vectors[3], floats[0], floats[1], floats[2]);
			}
			});
	}
	void InspectorPanelController::onSelectionChange(entt::entity entity)
	{
		mInspectorPanelModel->setSelectedEntity(entity);
	}
}

