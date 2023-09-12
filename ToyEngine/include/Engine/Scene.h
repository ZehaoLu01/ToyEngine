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
			MyScene():mRootEntity(entt::null) {
				mRootEntity = mRegistry.create();
			};
		private:
			entt::registry mRegistry;

			entt::entity mRootEntity;

			std::shared_ptr<Camera> mCamera;

	};
}