#pragma once
#include <memory>
#include"UI/Controller/Controller.h"
#include <entt/entt.hpp>
#include "UI/Model/FileExplorerModel.h"

namespace ui {
	class FileExplorerController : public Controller
	{
	public:
		FileExplorerController(std::unique_ptr<FileExplorerModel> model, entt::registry& registry);

		virtual void registerBindings() override;

		virtual void onSelectionChange(entt::entity entity) override;

	private:

		entt::registry& mRegistry;
		std::unique_ptr<FileExplorerModel> mFileExplorerModel;
	};
}


