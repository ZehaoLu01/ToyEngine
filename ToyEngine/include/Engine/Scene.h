#pragma once

#include<entt/entt.hpp>
#include<memory>
#include<vector>
#include <Renderer/Camera.h>
#include <tuple>
#include <Engine/Component.h>
#include <entt/entt.hpp>


namespace ToyEngine {
	class MyScene {
		public:
			void init();

			void update();
			void processRendering();
			MyScene() = default;

			entt::registry& getRegistry() {
				return mRegistry;
			}

			entt::entity getRootEntity() {
				return mRootEntity;
			}

			std::tuple<std::vector<entt::entity>, std::vector<entt::entity>, std::vector<entt::entity>> getLightEntities();

			void addLighting() {
				auto entity = mRegistry.create();
				mRegistry.emplace<LightComponent>(entity, "point");
				mRegistry.emplace<TransformComponent>(entity);
			}
		private:
			entt::registry mRegistry;

			std::vector<entt::entity> mEntityList;

			std::shared_ptr<Camera> mCamera;

			entt::entity mRootEntity;
	};
}