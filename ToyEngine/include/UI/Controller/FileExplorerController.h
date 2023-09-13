#pragma once
#include <memory>
#include"UI/Controller/Controller.h"
#include <entt/entt.hpp>

namespace ui {
	class FileExplorerController : public Controller
	{
	public:
		FileExplorerController(entt::registry& registry);

		virtual void registerBindings() override;

		virtual void onSelectionChange(entt::entity entity) override;

	private:

		entt::registry& mRegistry;
	};
}


