#pragma once
#include <memory>
#include"UI/Controller/Controller.h"
#include <entt/entt.hpp>

namespace ui {
	class FileExplorerController : public Controller, public std::enable_shared_from_this<FileExplorerController>
	{
	public:
		FileExplorerController(entt::registry& registry);

		virtual void registerBindings() override;

	private:

		entt::registry& mRegistry;
	};
}


