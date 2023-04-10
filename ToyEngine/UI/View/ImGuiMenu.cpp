#include "UI/View/ImGuiMenu.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <sstream>
#include "UI/Controller/PropertiesScreenController.h"

namespace ui{
	void ImGuiMenu::tick()
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
		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		ImGui::ShowDemoWindow(&p_open);

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
		renderObjectPropertyMenu();

		renderHierarchyMenu();

		renderLoggingMenu();

		ImGui::End();
		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		mController->tick();
	}

	void ImGuiMenu::renderHierarchyMenu()
	{
		ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_NoMove);                          // Create a window called "Hello, world!" and append into it.


		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	void ImGuiMenu::renderLoggingMenu()
	{
		//mFileBrowser->Open();

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		mFileBrowser->Display();

		mFileExplorer->render();
	}

	void ImGuiMenu::renderObjectPropertyMenu()
	{
		ImGui::Begin("Renderer Settings", nullptr, ImGuiWindowFlags_NoMove);                          // Create a window called "Hello, world!" and append into it.

		if (ImGui::CollapsingHeader("Object properties")) {
			drawPositionProps();

			drawRotationProps();

			drawScaleProps();
		}

		if (ImGui::CollapsingHeader("Lighting properties")) {
			drawLightProps();
		}

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	void ImGuiMenu::setController(std::shared_ptr<PropertiesScreenController> controller)
	{
		mController = controller;
		mController->registerBindings();
	}

	ImGuiMenu::ImGuiMenu()
	{
		mController = std::make_shared<ui::PropertiesScreenController>();
	}

	void ImGuiMenu::drawPositionProps() {
		glm::vec3 oldPositionVal = mController->getVec("properties.position");
		glm::vec3 newPositionVal = oldPositionVal;

		ImGui::Text("POSITION");
		if (ImGui::BeginTable("axis", 3, ImGuiTableFlags_Borders)) {
			ImGui::TableNextColumn();
			ImGui::Text("x: ");
			ImGui::InputFloat("##value pos_x", &newPositionVal.x);
			ImGui::Text("current val: %f", oldPositionVal.x);

			ImGui::TableNextColumn();
			ImGui::Text("y: ");
			ImGui::InputFloat("##value pos_y", &newPositionVal.y);
			ImGui::Text("current val: %f", oldPositionVal.y);

			ImGui::TableNextColumn();
			ImGui::Text("z: ");
			ImGui::InputFloat("##value pos_z", &newPositionVal.z);
			ImGui::Text("current val: %f", oldPositionVal.z);

			ImGui::EndTable();

			if (oldPositionVal != newPositionVal) {
				mController->addViewEvent({ ViewEventType::InputEvent,"properties.position",BindingValueType::Vec3, getVec3String(newPositionVal) });
			}
		}
	}

	void ImGuiMenu::drawRotationProps()
	{
		glm::vec3 oldRotationVal = mController->getVec("properties.rotation");
		glm::vec3 newRotationVal = oldRotationVal;

		ImGui::Text("ROTATION");
		if (ImGui::BeginTable("axis", 3, ImGuiTableFlags_Borders)) {
			ImGui::TableNextColumn();
			ImGui::Text("pitch: ");
			ImGui::InputFloat("##value pitch", &newRotationVal.x);
			ImGui::Text("current val: %f", oldRotationVal.x);


			ImGui::TableNextColumn();
			ImGui::Text("yaw: ");
			ImGui::InputFloat("##value yaw", &newRotationVal.y);
			ImGui::Text("current val: %f", oldRotationVal.y);

			ImGui::TableNextColumn();
			ImGui::Text("row: ");
			ImGui::InputFloat("##value row", &newRotationVal.z);
			ImGui::Text("current val: %f", oldRotationVal.z);

			ImGui::EndTable();

			if (oldRotationVal != newRotationVal) {
				mController->addViewEvent({ ViewEventType::InputEvent,"properties.rotation",BindingValueType::Vec3, getVec3String(newRotationVal) });
			}
		}
	}

	void ImGuiMenu::drawScaleProps()
	{
		glm::vec3 oldScaleVal = mController->getVec("properties.scale");
		glm::vec3 newScaleVal = oldScaleVal;
		ImGui::Text("SCALE");
		if (ImGui::BeginTable("axis", 3, ImGuiTableFlags_Borders)) {
			ImGui::TableNextColumn();
			ImGui::Text("x: ");
			ImGui::InputFloat("##value scale_x", &newScaleVal.x);
			ImGui::Text("current val: %f", oldScaleVal.x);

			ImGui::TableNextColumn();
			ImGui::Text("y: ");
			ImGui::InputFloat("##value scale_y", &newScaleVal.y);
			ImGui::Text("current val: %f", oldScaleVal.y);

			ImGui::TableNextColumn();
			ImGui::Text("z: ");
			ImGui::InputFloat("##value scale_z", &newScaleVal.z);
			ImGui::Text("current val: %f", oldScaleVal.z);

			ImGui::EndTable();

			if (oldScaleVal != newScaleVal) {
				mController->addViewEvent({ ViewEventType::InputEvent,"properties.scale",BindingValueType::Vec3, getVec3String(newScaleVal) });
			}
		}
	}

	void ImGuiMenu::drawLightProps()
	{
		// temp value
		static float point_light_position_x = 0.0f;
		static float point_light_position_y = 0.0f;
		static float point_light_position_z = 0.0f;

		ImGui::Text("POSITION");
		if (ImGui::BeginTable("axis", 3, ImGuiTableFlags_Borders)) {
			ImGui::TableNextColumn();
			ImGui::Text("x: ");
			ImGui::InputFloat("##value x", &point_light_position_x);
			ImGui::Text("current val: %f", point_light_position_x);

			ImGui::TableNextColumn();
			ImGui::Text("y: ");
			ImGui::InputFloat("##value y", &point_light_position_y);
			ImGui::Text("current val: %f", point_light_position_y);

			ImGui::TableNextColumn();
			ImGui::Text("z: ");
			ImGui::InputFloat("##value z", &point_light_position_z);
			ImGui::Text("current val: %f", point_light_position_z);

			ImGui::EndTable();
		}
	}

	std::string ImGuiMenu::getVec3String(glm::vec3 vec) {
		std::stringstream ss;
		ss << vec.x << "," << vec.y << "," << vec.z;
		return ss.str();
	}
}
