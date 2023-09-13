#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "UI/Model/ScreenModel.h"
#include <memory>
#include <entt/entt.hpp>
#include <Engine/Component.h>

namespace ui {
	class PropertiesScreenModel: public ScreenModel, public std::enable_shared_from_this<PropertiesScreenModel> {

	public:
		PropertiesScreenModel(entt::registry& registry);

		glm::vec3 getPosition() {
			if (mSelectedEntity!=entt::null) {
				return mRegistry.get<ToyEngine::TransformComponent>(mSelectedEntity).worldPos;
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
			mRegistry.patch<ToyEngine::TransformComponent>(mSelectedEntity, [position](ToyEngine::TransformComponent& transform) {transform.worldPos = position; });
		}
		void setRotation(glm::vec3 rotation) {
			mRegistry.patch<ToyEngine::TransformComponent>(mSelectedEntity, [rotation](ToyEngine::TransformComponent& transform) {transform.rotation_eular = rotation; });
		}
		void setScale(glm::vec3 scale) {

			mRegistry.patch<ToyEngine::TransformComponent>(mSelectedEntity, [scale](ToyEngine::TransformComponent& transform) {transform.scale = scale; });

		}

	private:
		glm::vec3 mPosition;
		glm::vec3 mRotation;
		glm::vec3 mScale;

		entt::registry& mRegistry;
	};
}