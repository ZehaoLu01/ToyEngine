#pragma once
#include <glm/ext/vector_float3.hpp>
#include <unordered_map>
#include <functional>
#include <string>
#include <memory>
#include <entt/entity/fwd.hpp>
namespace ui{

	class ScreenModel
	{
	public:
		entt::entity mSelectedEntity;

		void setSelectedEntity(entt::entity entity) {
			mSelectedEntity = entity;
		}

	};

}

