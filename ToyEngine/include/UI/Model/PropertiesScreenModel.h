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
			if (!mSelectedEntity.empty()) {
				return mRegistry.get<ToyEngine::TransformComponent>(mSelectedEntity[0]).worldPos;
			}
			return glm::vec3();
		}

		glm::vec3 getRotation() {
			if (!mSelectedEntity.empty()) {
				return mRegistry.get<ToyEngine::TransformComponent>(mSelectedEntity[0]).rotation_eular;
			}
			return glm::vec3();
		}

		glm::vec3 getScale() {
			if (!mSelectedEntity.empty()) {
				return mRegistry.get<ToyEngine::TransformComponent>(mSelectedEntity[0]).scale;
			}
			return glm::vec3();
		}

		void setPosition(glm::vec3 position) {
			for (auto selected : mSelectedEntity) {
				mRegistry.patch<ToyEngine::TransformComponent>(selected, [position](ToyEngine::TransformComponent& transform) {transform.worldPos = position; });
			}
		}
		void setRotation(glm::vec3 rotation) {
			for (auto selected : mSelectedEntity) {
				mRegistry.patch<ToyEngine::TransformComponent>(selected, [rotation](ToyEngine::TransformComponent& transform) {transform.rotation_eular = rotation; });
			}
		}
		void setScale(glm::vec3 scale) {
			for (auto selected : mSelectedEntity) {
				mRegistry.patch<ToyEngine::TransformComponent>(selected, [scale](ToyEngine::TransformComponent& transform) {transform.scale = scale; });
			}
		}

		void setSelectedEntity(const std::vector<entt::entity>& input) {
			mSelectedEntity = std::vector<entt::entity>(input.begin(), input.end());
		}

	private:
		glm::vec3 mPosition;
		glm::vec3 mRotation;
		glm::vec3 mScale;

		entt::registry& mRegistry;

		std::vector<entt::entity> mSelectedEntity;
	};
}