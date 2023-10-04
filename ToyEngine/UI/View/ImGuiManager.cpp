#include "UI/View/ImGuiManager.h"
#include <glm/gtx/string_cast.hpp>

namespace ui{
	void ImGuiManager::tick()
	{
		ImGuiIO& io = ImGui::GetIO();
		// must enable docking before using docking!
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		// full screen
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
		window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::Begin("docking", nullptr, window_flags);
		ImGui::PopStyleVar(2);

		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		bool p_open = true;

		ImGui::ShowDemoWindow(&p_open);
		
		mPropertiesScreen.render();

		mHierarchyPanel.render();

		renderLoggingMenu();

		ImGui::End();

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		// TODO: use parent class (Controller)
		mPropertiesScreenController->tick();
		mHierarchyContorller->tick();
		mFileExplorerController->tick();
	}

	void ImGuiManager::renderLoggingMenu()
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		mFileExplorer.render();
	}

	ImGuiManager& ImGuiManager::getInstance()
	{
		static ImGuiManager instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	}

	void ImGuiManager::setupControllers(std::shared_ptr<ToyEngine::Scene> scene)
	{
		mHierarchyContorller = std::make_shared<SceneHierarchyController>(std::make_unique<SceneHierarchyModel>(scene->getRegistry()));
		mPropertiesScreenController = std::make_shared<PropertiesScreenController>(std::make_unique<PropertiesScreenModel>(scene));

		//TODO: Maybe I should use file explorer model.
		mFileExplorerController = std::make_shared<FileExplorerController>(scene->getRegistry());

		mScreenControllers = std::vector<std::shared_ptr<Controller>>({mHierarchyContorller,mPropertiesScreenController,mFileExplorerController});

		for (auto controller : mScreenControllers) {
			controller->init();
		}

		mContext = scene;

		mPropertiesScreen = PropertiesScreen(mContext, mPropertiesScreenController);
		mHierarchyPanel = SceneHierarchyPanel(scene, mHierarchyContorller, [](entt::entity entity) {
			ViewEvent event(ImGuiManager::getInstance().mContext->getRegistry());
			event.viewEventType = ViewEventType::ButtonEvent;
			event.name = "changeSelectionButtonDown";
			event.value = std::to_string((uint32_t)entity);

			for (auto controller : ImGuiManager::getInstance().mScreenControllers) {
				controller->addViewEvent(event);
			}
			}
		);
		mFileExplorer = FileExplorer(mFileExplorerController, scene);

	}

	ImGuiManager::ImGuiManager()
	{
	}
}
