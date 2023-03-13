#include "ImGuiMenu.h"


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>

void ImGuiMenu::tick()
{
	ImGuiIO& io = ImGui::GetIO();
	// must enable docking before using docking!
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

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

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window) {
		ImGui::ShowDemoWindow(&show_demo_window);
	}


	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Renderer Settings");                          // Create a window called "Hello, world!" and append into it.

		if (ImGui::CollapsingHeader("Object properties")) {
			drawPositionProps();

			drawRotationProps();

			drawScaleProps();
		}

		if (ImGui::CollapsingHeader("Lighting properties")) {
			drawLightProps();
		}

		if (ImGui::Button("Set"))
			counter++;
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color


		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	ImGui::End();
	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiMenu::setWorldPos(glm::vec3 worldPos)
{
	mWorldPos = worldPos;
}

void ImGuiMenu::setRotation(glm::vec3 rotation)
{
	mRotation = rotation;
}

void ImGuiMenu::setScale (glm::vec3 scale)
{
	mScale = scale;
}

glm::vec3 ImGuiMenu::getWorldPos()
{
	return mWorldPos;
}

glm::vec3 ImGuiMenu::getRotation()
{
	return mRotation;
}

glm::vec3 ImGuiMenu::getScale()
{
	return mScale;
}

void ImGuiMenu::drawPositionProps() {
	ImGui::Text("POSITION");
	if (ImGui::BeginTable("axis", 3, ImGuiTableFlags_Borders)) {
		ImGui::TableNextColumn();
		ImGui::Text("x: ");
		ImGui::InputFloat("##value pos_x", &mWorldPos.x);
		ImGui::Text("current val: %f", mWorldPos.x);

		ImGui::TableNextColumn();
		ImGui::Text("y: ");
		ImGui::InputFloat("##value pos_y", &mWorldPos.y);
		ImGui::Text("current val: %f", mWorldPos.y);

		ImGui::TableNextColumn();
		ImGui::Text("z: ");
		ImGui::InputFloat("##value pos_z", &mWorldPos.z);
		ImGui::Text("current val: %f", mWorldPos.z);

		ImGui::EndTable();
	}
}

void ImGuiMenu::drawRotationProps()
{
	ImGui::Text("ROTATION");
	if (ImGui::BeginTable("axis", 3, ImGuiTableFlags_Borders)) {
		ImGui::TableNextColumn();
		ImGui::Text("pitch: ");
		ImGui::InputFloat("##value pitch", &mRotation.x);
		ImGui::Text("current val: %f", mRotation.x);


		ImGui::TableNextColumn();
		ImGui::Text("yaw: ");
		ImGui::InputFloat("##value yaw", &mRotation.y);
		ImGui::Text("current val: %f", mRotation.y);

		ImGui::TableNextColumn();
		ImGui::Text("row: ");
		ImGui::InputFloat("##value row", &mRotation.z);
		ImGui::Text("current val: %f", mRotation.z);

		ImGui::EndTable();
	}
}

void ImGuiMenu::drawScaleProps()
{
	ImGui::Text("SCALE");
	if (ImGui::BeginTable("axis", 3, ImGuiTableFlags_Borders)) {
		ImGui::TableNextColumn();
		ImGui::Text("x: ");
		ImGui::InputFloat("##value scale_x", &mScale.x);
		ImGui::Text("current val: %f", mScale.x);

		ImGui::TableNextColumn();
		ImGui::Text("y: ");
		ImGui::InputFloat("##value scale_y", &mScale.y);
		ImGui::Text("current val: %f", mScale.y);

		ImGui::TableNextColumn();
		ImGui::Text("z: ");
		ImGui::InputFloat("##value scale_z", &mScale.z);
		ImGui::Text("current val: %f", mScale.z);

		ImGui::EndTable();
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