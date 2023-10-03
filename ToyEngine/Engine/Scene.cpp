#include "Engine/Scene.h"
#include <Engine/Engine.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <Renderer/RenderSystem.h>
#include <Engine/Component.h>

namespace ToyEngine {
    void Scene::update()
    {
        processRendering();
    }

    void Scene::processRendering()
    {
        auto view = mRegistry.view<MeshComponent, TransformComponent, MaterialComponent>();

        RenderSystem::instance.preDraw();

        RenderSystem::instance.drawGridLine();
        RenderSystem::instance.drawCoordinateIndicator({ 0,0,0 });

        for (auto entity : view) {
            // reference?
            auto [mesh, transform, texture] = mRegistry.get<MeshComponent, TransformComponent, MaterialComponent>(entity);
            RenderSystem::instance.drawMesh(transform, mesh, texture);
        }

        RenderSystem::instance.drawLightingCube();

        RenderSystem::instance.drawImGuiMenu();

        RenderSystem::instance.afterDraw();
    }

    void Scene::init()
    {
        mRootEntity = mRegistry.create();
        auto transform = mRegistry.emplace<TransformComponent>(mRootEntity);
    }

    std::tuple<std::vector<entt::entity>, std::vector<entt::entity>, std::vector<entt::entity>> Scene::getLightEntities() {
        // get all entities in the ecs that have a light component
        auto entityHandles = mRegistry.view<LightComponent>();
        std::vector<entt::entity> directionalLights, pointLights, spotLights;

        for (auto entityHandle : entityHandles) {
            entt::entity entity = { entityHandle };

            std::string lightType = mRegistry.get<LightComponent>(entity).type;

            if (lightType == "directional") {
                directionalLights.push_back(entity);
            }
            else if (lightType == "point") {
                pointLights.push_back(entity);
            }
            else if (lightType == "spotlight") {
                spotLights.push_back(entity);
            }
            else {
                std::cerr << "Invalid light type detected in Light component: " + lightType << std::endl;
            }
        }

        return { directionalLights, pointLights, spotLights };
    }

    void Scene::addPointLight()
    {
        auto entity = mRegistry.create();
        mRegistry.emplace<LightComponent>(entity, "point");
        mRegistry.emplace<TransformComponent>(entity);
        mRegistry.emplace<TagComponent>(entity, "pointLight");
        mRegistry.emplace<RelationComponent>(entity);
    }

    void Scene::addPointLight(glm::vec3 pos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic) {
        auto entity = mRegistry.create();
        mRegistry.emplace<LightComponent>(entity, "point", ambient, diffuse, specular, constant, linear, quadratic);
        mRegistry.emplace<TransformComponent>(entity, pos, glm::vec3{.0f,.0f,.0f}, glm::vec3{ .0f,.0f,.0f });
        mRegistry.emplace<TagComponent>(entity, "pointLight");
        mRegistry.emplace<RelationComponent>(entity);
    }
}
