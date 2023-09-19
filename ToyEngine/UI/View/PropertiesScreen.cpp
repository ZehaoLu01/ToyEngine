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
			ImGui::DragFloat("##value pos_x", &newPositionVal.x);

			ImGui::TableNextColumn();
			ImGui::Text("y: ");
			ImGui::DragFloat("##value pos_y", &newPositionVal.y);

			ImGui::TableNextColumn();
			ImGui::Text("z: ");
			ImGui::DragFloat("##value pos_z", &newPositionVal.z);

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
			ImGui::DragFloat("##value pitch", &newRotationVal.x, 5.0f);


			ImGui::TableNextColumn();
			ImGui::Text("yaw: ");
			ImGui::DragFloat("##value yaw", &newRotationVal.y, 5.0f);

			ImGui::TableNextColumn();
			ImGui::Text("row: ");
			ImGui::DragFloat("##value row", &newRotationVal.z, 5.0f);

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
			ImGui::DragFloat("##value scale_x", &newScaleVal.x, 0.1f);

			ImGui::TableNextColumn();
			ImGui::Text("y: ");
			ImGui::DragFloat("##value scale_y", &newScaleVal.y, 0.1f);

			ImGui::TableNextColumn();
			ImGui::Text("z: ");
			ImGui::DragFloat("##value scale_z", &newScaleVal.z, 0.1f);

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
		static glm::vec3 point_light_position = { .0f,.0f,.0f };
		static glm::vec3 point_light_ambient = { 1.0f, 1.0f, 1.0f };
		static glm::vec3 point_light_diffuse = { 1.0f, 1.0f, 1.0f };
		static glm::vec3 point_light_specular = { 1.0f, 1.0f, 1.0f };

		static float constant = 1.0f;
		static float linear = 0.09f;
		static float quadratic = 0.032f;


		ImGui::Text("Position");
		if (ImGui::BeginTable("axis", 3, ImGuiTableFlags_Borders)) {
			ImGui::TableNextColumn();
			ImGui::Text("x: ");
			ImGui::DragFloat("##value x", &point_light_position.x, 0.1f);

			ImGui::TableNextColumn();
			ImGui::Text("y: ");
			ImGui::DragFloat("##value y", &point_light_position.y, 0.1f);

			ImGui::TableNextColumn();
			ImGui::Text("z: ");
			ImGui::DragFloat("##value z", &point_light_position.z, 0.1f);

			ImGui::EndTable();
		}

		ImGui::Text("Ambient");
		if (ImGui::BeginTable("axis", 3, ImGuiTableFlags_Borders)) {
			ImGui::TableNextColumn();
			ImGui::Text("x: ");
			ImGui::DragFloat("##value x", &point_light_ambient.x, 0.1f);

			ImGui::TableNextColumn();
			ImGui::Text("y: ");
			ImGui::DragFloat("##value y", &point_light_ambient.y, 0.1f);

			ImGui::TableNextColumn();
			ImGui::Text("z: ");
			ImGui::DragFloat("##value z", &point_light_ambient.z, 0.1f);

			ImGui::EndTable();
		}

		ImGui::Text("Diffuse");
		if (ImGui::BeginTable("axis", 3, ImGuiTableFlags_Borders)) {
			ImGui::TableNextColumn();
			ImGui::Text("x: ");
			ImGui::DragFloat("##value x", &point_light_diffuse.x, 0.1f);

			ImGui::TableNextColumn();
			ImGui::Text("y: ");
			ImGui::DragFloat("##value y", &point_light_diffuse.y, 0.1f);

			ImGui::TableNextColumn();
			ImGui::Text("z: ");
			ImGui::DragFloat("##value z", &point_light_diffuse.z, 0.1f);

			ImGui::EndTable();
		}

		ImGui::Text("Specular");
		if (ImGui::BeginTable("axis", 3, ImGuiTableFlags_Borders)) {
			ImGui::TableNextColumn();
			ImGui::Text("x: ");
			ImGui::DragFloat("##value x", &point_light_specular.x, 0.1f);

			ImGui::TableNextColumn();
			ImGui::Text("y: ");
			ImGui::DragFloat("##value y", &point_light_specular.y, 0.1f);

			ImGui::TableNextColumn();
			ImGui::Text("z: ");
			ImGui::DragFloat("##value z", &point_light_specular.z, 0.1f);

			ImGui::EndTable();
		}

		ImGui::Text("Coefficients");
		if (ImGui::BeginTable("axis", 3, ImGuiTableFlags_Borders)) {
			ImGui::TableNextColumn();
			ImGui::Text("constants: ");
			ImGui::DragFloat("##value x", &constant, 0.1f);

			ImGui::TableNextColumn();
			ImGui::Text("linear: ");
			ImGui::DragFloat("##value y", &linear, 0.1f);

			ImGui::TableNextColumn();
			ImGui::Text("quadratic: ");
			ImGui::DragFloat("##value z", &quadratic, 0.1f);

			ImGui::EndTable();
		}

		if (ImGui::Button("Add light cube")) {
			ViewEvent event(mContext->getRegistry());
			event.viewEventType = ViewEventType::ButtonEvent;
			event.name = "onCreateLightCubeButtonDown";
			event.vectorGroup = { point_light_position,point_light_ambient, point_light_diffuse, point_light_specular };
			event.floatGroup = {constant, linear, quadratic};
			mPropertiesScreenController->addViewEvent(event);
		}
	}

	std::string PropertiesScreen::getVec3String(glm::vec3 vec) {
		std::stringstream ss;
		ss << vec.x << "," << vec.y << "," << vec.z;
		return ss.str();
	}
}
