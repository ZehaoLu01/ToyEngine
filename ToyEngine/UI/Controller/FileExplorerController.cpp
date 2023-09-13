#include <UI/Controller/FileExplorerController.h>
#include <Renderer/RenderSystem.h>

namespace ui {
	FileExplorerController::FileExplorerController(entt::registry& registry):mRegistry(registry)
	{
	}
	void FileExplorerController::registerBindings()
	{
		bindButtonInteractHandler("onModelFileButtonDown", [](const ViewEvent& event) {
			ToyEngine::RenderSystem::instance.loadModel(event.path, event.value, event.registry);
		});

	}
	void FileExplorerController::onSelectionChange(entt::entity entity)
	{
		
	}
}
