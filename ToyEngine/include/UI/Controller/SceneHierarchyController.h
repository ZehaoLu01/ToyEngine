#pragma once
#include <memory>
#include <UI/Controller/Controller.h>
#include <UI/Model/SceneHierarchyModel.h>

namespace ui {
	class SceneHierarchyController : public Controller
	{
	public:
		SceneHierarchyController(entt::registry& registry);

		virtual void registerBindings() override {
		
		};

		std::vector<std::string> getTagNames();

		virtual void onSelectionChange(entt::entity) override;

	private:
		std::shared_ptr<ui::SceneHierarchyModel> mSceneHierarchyModel;

		entt::registry& mRegistry;
	};
}


