//#pragma once
//#include <glad/glad.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include "UI/Model/ScreenModel.h"
//#include <memory>
//
//
//namespace ui {
//	class PropertiesScreenModel: public ScreenModel, public std::enable_shared_from_this<PropertiesScreenModel> {
//
//	public:
//		PropertiesScreenModel();
//		PropertiesScreenModel(std::vector<std::shared_ptr<ToyEngine::RenderComponent>> defaultSelectedComponents);
//
//		glm::vec3 getPosition() {
//			if (!mSelectedRenderComponents.empty()) {
//				return mSelectedRenderComponents[0]->getWorldPosition();
//			}
//			return glm::vec3();
//		}
//
//		glm::vec3 getRotation() {
//			if (!mSelectedRenderComponents.empty()) {
//				return mSelectedRenderComponents[0]->getRotationEular();
//			}
//			return glm::vec3();
//		}
//
//		glm::vec3 getScale() {
//			if (!mSelectedRenderComponents.empty()) {
//				return mSelectedRenderComponents[0]->getScale();
//			}
//			return glm::vec3();
//		}
//
//		void setPosition(glm::vec3 position) {
//			for(auto selectedComponent : mSelectedRenderComponents) {
//				selectedComponent->setWorldPosition(position);
//			}
//		}
//		void setRotation(glm::vec3 rotation) {
//			for (auto selectedComponent : mSelectedRenderComponents) {
//				selectedComponent->setRotationEular(rotation);
//			}
//		}
//		void setScale(glm::vec3 scale) {
//			for (auto selectedComponent : mSelectedRenderComponents) {
//				selectedComponent->setScale(scale);
//			}
//		}
//
//		void setSelectedRenderComponents(std::vector<std::shared_ptr<ToyEngine::RenderComponent>>& renderComponents) {
//			mSelectedRenderComponents = renderComponents;
//		}
//
//	private:
//		glm::vec3 mPosition;
//		glm::vec3 mRotation;
//		glm::vec3 mScale;
//
//		std::vector<std::shared_ptr<ToyEngine::RenderComponent>> mSelectedRenderComponents;
//	};
//}