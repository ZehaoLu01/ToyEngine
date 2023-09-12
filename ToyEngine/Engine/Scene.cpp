#include "Engine/Scene.h"
#include <Engine/Engine.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <Renderer/RenderSystem.h>

void ToyEngine::MyScene::update()
{
	auto group = mRegistry.group<MeshComponent, TransformComponent, TextureComponent>();
	
	RenderSystem::instance.preDraw();

	RenderSystem::instance.drawGridLine();
	RenderSystem::instance.drawCoordinateIndicator({0,0,0});

	for (auto entity : group) {
		// reference?
		auto [transform, mesh, texture] = group.get<TransformComponent, MeshComponent, TextureComponent>(entity);
		RenderSystem::instance.drawMesh(transform, mesh, texture);
	}

	RenderSystem::instance.drawImGuiMenu();

	RenderSystem::instance.afterDraw();
}

void ToyEngine::MyScene::init()
{
	TransformComponent transform;

	entt::entity entity = mRegistry.create();

	// TODO: should remove this. This is for testing. The model is only for testing for now.
	auto created = RenderSystem::instance.loadModel("C:/repo/ToyEngine/ToyEngine/Resources/model/backpack.obj", "bag",mRegistry, entity, transform);
	mEntityList.push_back(created);
}

