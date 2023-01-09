#include "ImGuiMenu.h"


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

glm::vec3 ImGuiMenu::mWorldPos = glm::vec3();
glm::vec3 ImGuiMenu::mRotation = glm::vec3();
glm::vec3 ImGuiMenu::mScale = glm::vec3();

void ImGuiMenu::tick()
{
	// Testing I am gui
// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		static float position_x = 1.0f;
		static float position_y = 0.0f;
		static float position_z = 0.0f;

		static float rotation_pitch = 0.0f;
		static float rotation_yaw = 0.0f;
		static float rotation_roll = 0.0f;

		static float scale_x = 1.0f;
		static float scale_y = 1.0f;
		static float scale_z = 1.0f;


		ImGui::Begin("Renderer Settings");                          // Create a window called "Hello, world!" and append into it.

		if (ImGui::CollapsingHeader("Object properties")) {
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

		static float point_light_position_x = 0.0f;
		static float point_light_position_y = 0.0f;
		static float point_light_position_z = 0.0f;

		if (ImGui::CollapsingHeader("Lighting properties")) {
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

		if (ImGui::Button("Set"))
			counter++;
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color


		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::BeginChild("Scrolling");
		for (int n = 0; n < 50; n++)
			ImGui::Text("%04d: Some text", n);
		ImGui::EndChild();

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}

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