#include <UI/Controller/FileExplorerController.h>
#include <Renderer/RenderSystem.h>

namespace ui {
	FileExplorerController::FileExplorerController(entt::registry& registry):mRegistry(registry)
	{
	}
	void FileExplorerController::registerBindings()
	{
		auto weakThis = weak_from_this();

		bindButtonInteractHandler("onModelFileButtonDown", [weakThis](const ViewEvent& event) {
			ToyEngine::RenderSystem::instance.loadModel(event.path, event.value, event.registry);
		});

	}
}
