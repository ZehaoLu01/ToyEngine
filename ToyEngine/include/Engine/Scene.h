#pragma once

#include<entt/entity/registry.hpp>
#include<memory>
#include<vector>
#include <Renderer/Camera.h>


namespace ToyEngine {
	class MyScene {
		public:
			void init();

			void update();
			MyScene() = default;

			entt::registry& getRegistry() {
				return mRegistry;
			}

		private:
			entt::registry mRegistry;

			std::vector<entt::entity> mEntityList;

			std::shared_ptr<Camera> mCamera;

	};
}