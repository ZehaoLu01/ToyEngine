#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "UI/Model/ScreenModel.h"
#include <memory>
#include <entt/entt.hpp>
#include <Engine/Component.h>
#include <Engine/Scene.h>

namespace ui {
	class PropertiesScreenModel: public ScreenModel, public std::enable_shared_from_this<PropertiesScreenModel> {

	public:
		ui::PropertiesScreenModel(std::shared_ptr<ToyEngine::Scene> scene);


		glm::vec3 getPosition() {
			if (mSelectedEntity!=entt::null) {
				return mRegistry.get<ToyEngine::TransformComponent>(mSelectedEntity).localPos;
			}
			return glm::vec3();
		}

		glm::vec3 getRotation() {
			if (mSelectedEntity != entt::null) {
				return mRegistry.get<ToyEngine::TransformComponent>(mSelectedEntity).rotation_eular;
			}
			return glm::vec3();
		}

		glm::vec3 getScale() {
			if (mSelectedEntity != entt::null) {
				return mRegistry.get<ToyEngine::TransformComponent>(mSelectedEntity).scale;
			}
			return glm::vec3();
		}

		void setPosition(glm::vec3 position) {
			if (mSelectedEntity != entt::null) {
				mRegistry.patch<ToyEngine::TransformComponent>(mSelectedEntity, [position](ToyEngine::TransformComponent& transform) {transform.localPos = position; });
			}
		}
		void setRotation(glm::vec3 rotation) {
			if (mSelectedEntity != entt::null) {
				mRegistry.patch<ToyEngine::TransformComponent>(mSelectedEntity, [rotation](ToyEngine::TransformComponent& transform) {transform.rotation_eular = rotation; });
			}
		}
		void setScale(glm::vec3 scale) {
			if (mSelectedEntity != entt::null) {
				mRegistry.patch<ToyEngine::TransformComponent>(mSelectedEntity, [scale](ToyEngine::TransformComponent& transform) {transform.scale = scale; });
			}
		}

		void addLightCube() {
			mScene->addPointLight();
		}

		void addLightCube(glm::vec3 pos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic) {
			mScene->addPointLight(pos, ambient, diffuse, specular, constant, linear, quadratic);
		}

	private:
		std::shared_ptr<ToyEngine::Scene> mScene;
		

	};
}