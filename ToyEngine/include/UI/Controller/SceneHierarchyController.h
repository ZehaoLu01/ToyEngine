#pragma once
#include <memory>
#include <UI/Controller/Controller.h>
#include <UI/Model/SceneHierarchyModel.h>

namespace ui {
	class SceneHierarchyController : public Controller, public std::enable_shared_from_this<SceneHierarchyController>
	{
	public:
		SceneHierarchyController(entt::registry& registry);

		virtual void registerBindings() override {
		
		};

		std::vector<std::string> getTagNames();

	private:
		std::shared_ptr<ui::SceneHierarchyModel> mSceneHierarchyModel;

		entt::registry& mRegistry;
	};
}


