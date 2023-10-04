#pragma once

#include<entt/entt.hpp>
#include<memory>
#include<vector>
#include <Renderer/Camera.h>
#include <tuple>
#include <Engine/Component.h>
#include <entt/entt.hpp>


namespace ToyEngine {
	class Scene {
		public:
			void init();

			void update();
			void processRendering();
			Scene() = default;

			entt::registry& getRegistry() {
				return mRegistry;
			}

			entt::entity getRootEntity() {
				return mRootEntity;
			}

			std::tuple<std::vector<entt::entity>, std::vector<entt::entity>, std::vector<entt::entity>> getLightEntities();

			void addPointLight();
			void addPointLight(glm::vec3 pos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);
			void addDirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);

		private:
			entt::registry mRegistry;

			std::vector<entt::entity> mEntityList;

			std::shared_ptr<Camera> mCamera;

			entt::entity mRootEntity;
	};
}