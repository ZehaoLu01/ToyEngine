#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "UI/Model/ScreenModel.h"
#include <memory>
#include <entt/entt.hpp>
#include <vector>
#include <string>
#include <Engine/Component.h>

namespace ui {
	class SceneHierarchyModel : public ScreenModel{

	public:
		SceneHierarchyModel(entt::registry& registry);
		std::vector<std::string> getTagNames() {

			updateDictAndTags();

			return mTags;
		}

	private:
		void updateDictAndTags() {
			auto entities = mRegistry.view<ToyEngine::TagComponent>();
			for (const auto entity : entities) {
				std::string name = mRegistry.get<ToyEngine::TagComponent>(entity).name;
				mTags.push_back(name);
				mTagToEntityDict[name] = entity;
			}
		}

		std::vector<std::string> mTags;
		std::unordered_map<std::string, entt::entity> mTagToEntityDict;
	};
}