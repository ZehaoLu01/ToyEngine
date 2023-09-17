#include <UI/View/PropertiesScreen.h>
#include <glm/fwd.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <UI/Controller/PropertiesScreenController.h>


namespace ui {
	void PropertiesScreen::render() {
		renderObjectPropertyMenu();
	}

	void PropertiesScreen::renderObjectPropertyMenu()
	{
		ImGui::Begin("Renderer Settings", nullptr, ImGuiWindowFlags_NoMove);

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

	void PropertiesScreen::drawPositionProps() {
		glm::vec3 oldPositionVal = mPropertiesScreenController->getVec("properties.position");
		glm::vec3 newPositionVal = oldPositionVal;

		ImGui::Text("POSITION");
		if (ImGui::BeginTable("axis", 3, ImGuiTableFlags_Borders)) {
			ImGui::TableNextColumn();
			ImGui::Text("x: ");
			ImGui::InputFloat("##value pos_x", &newPositionVal.x);

			ImGui::TableNextColumn();
			ImGui::Text("y: ");
			ImGui::InputFloat("##value pos_y", &newPositionVal.y);

			ImGui::TableNextColumn();
			ImGui::Text("z: ");
			ImGui::InputFloat("##value pos_z", &newPositionVal.z);

			ImGui::EndTable();

			ViewEvent event(mContext->getRegistry());
			event.viewEventType = ViewEventType::InputEvent;
			event.name = "properties.position";
			event.valueType = BindingValueType::Vec3;
			event.value = getVec3String(newPositionVal);

			if (oldPositionVal != newPositionVal) {
				mPropertiesScreenController->addViewEvent(event);
			}
		}
	}

	void PropertiesScreen::drawRotationProps()
	{
		glm::vec3 oldRotationVal = mPropertiesScreenController->getVec("properties.rotation");
		glm::vec3 newRotationVal = oldRotationVal;

		ImGui::Text("ROTATION");
		if (ImGui::BeginTable("axis", 3, ImGuiTableFlags_Borders)) {
			ImGui::TableNextColumn();
			ImGui::Text("pitch: ");
			ImGui::InputFloat("##value pitch", &newRotationVal.x);


			ImGui::TableNextColumn();
			ImGui::Text("yaw: ");
			ImGui::InputFloat("##value yaw", &newRotationVal.y);

			ImGui::TableNextColumn();
			ImGui::Text("row: ");
			ImGui::InputFloat("##value row", &newRotationVal.z);

			ImGui::EndTable();

			ViewEvent event(mContext->getRegistry());
			event.viewEventType = ViewEventType::InputEvent;
			event.name = "properties.rotation";
			event.valueType = BindingValueType::Vec3;
			event.value = getVec3String(newRotationVal);

			if (oldRotationVal != newRotationVal) {
				mPropertiesScreenController->addViewEvent(event);
			}
		}
	}

	void PropertiesScreen::drawScaleProps()
	{
		glm::vec3 oldScaleVal = mPropertiesScreenController->getVec("properties.scale");
		glm::vec3 newScaleVal = oldScaleVal;
		ImGui::Text("SCALE");
		if (ImGui::BeginTable("axis", 3, ImGuiTableFlags_Borders)) {
			ImGui::TableNextColumn();
			ImGui::Text("x: ");
			ImGui::InputFloat("##value scale_x", &newScaleVal.x);

			ImGui::TableNextColumn();
			ImGui::Text("y: ");
			ImGui::InputFloat("##value scale_y", &newScaleVal.y);

			ImGui::TableNextColumn();
			ImGui::Text("z: ");
			ImGui::InputFloat("##value scale_z", &newScaleVal.z);

			ImGui::EndTable();

			ViewEvent event(mContext->getRegistry());
			event.viewEventType = ViewEventType::InputEvent;
			event.name = "properties.scale";
			event.valueType = BindingValueType::Vec3;
			event.value = getVec3String(newScaleVal);


			if (oldScaleVal != newScaleVal) {
				mPropertiesScreenController->addViewEvent(event);
			}
		}
	}

	void PropertiesScreen::drawLightProps()
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

			ImGui::TableNextColumn();
			ImGui::Text("y: ");
			ImGui::InputFloat("##value y", &point_light_position_y);

			ImGui::TableNextColumn();
			ImGui::Text("z: ");
			ImGui::InputFloat("##value z", &point_light_position_z);

			ImGui::EndTable();
		}

		if (ImGui::Button("Add light cube")) {
			ViewEvent event(mContext->getRegistry());
			event.viewEventType = ViewEventType::ButtonEvent;
			event.name = "onCreateLightCubeButtonDown";
			mPropertiesScreenController->addViewEvent(event);
		}
	}

	std::string PropertiesScreen::getVec3String(glm::vec3 vec) {
		std::stringstream ss;
		ss << vec.x << "," << vec.y << "," << vec.z;
		return ss.str();
	}
}
