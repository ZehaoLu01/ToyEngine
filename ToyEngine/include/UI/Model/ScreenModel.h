#pragma once
#include <glm/ext/vector_float3.hpp>
#include <unordered_map>
#include <functional>
#include <string>
#include <memory>
#include <entt/entt.hpp>
namespace ui{

	class ScreenModel
	{
	public:
		ScreenModel(entt::registry& registry) :mRegistry(registry) {};

		entt::entity mSelectedEntity=entt::null;

		void setSelectedEntity(entt::entity entity) {
			mSelectedEntity = entity;
		}
		
		entt::registry& getRegistry() {
			return mRegistry;
		}

	protected:
		entt::registry& mRegistry;
	};

}

