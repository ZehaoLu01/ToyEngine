#include <UI/Controller/FileExplorerController.h>
#include <Renderer/RenderSystem.h>

namespace ui {
	FileExplorerController::FileExplorerController(std::unique_ptr<FileExplorerModel> model, entt::registry& registry)
		:mFileExplorerModel(std::move(model)), mRegistry(registry)
	{
	}

	void FileExplorerController::registerBindings()
	{
		auto weakThis = weak_from_this();
		bindButtonInteractHandler("onModelFileButtonDown", [weakThis](const ViewEvent& event) {
			if (auto sharedThis = std::dynamic_pointer_cast<FileExplorerController>(weakThis.lock())) {
				auto parentTransform = sharedThis->mRegistry.get<ToyEngine::TransformComponent>(event.parentEntity);
				ToyEngine::RenderSystem::instance.loadModel(event.path, event.value, event.registry, event.parentEntity);
			} 
		});
	}

	void FileExplorerController::onSelectionChange(entt::entity entity)
	{
	}
}
