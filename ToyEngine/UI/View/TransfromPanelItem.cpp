#include <Utils/RenderHelper.h>
#include <UI/View/TransfromPanelItem.h>
#include <UI/View/ImGuiManager.h>
#include <UI/Controller/Controller.h>

void ui::TransfromPanelItem::renderContent()
{
	drawPositionSetting();
	drawRotationSetting();
	drawScaleSetting();
}

void ui::TransfromPanelItem::drawScaleSetting()
{
	glm::vec3 oldScaleVal = mController->getVec("properties.scale");
	glm::vec3 newScaleVal = oldScaleVal;
	ImGui::Text("SCALE");
	if (ImGui::BeginTable("axis", 3, ImGuiTableFlags_Borders)) {
		ImGui::TableNextColumn();
		ImGui::Text("x: ");
		ImGui::DragFloat(wrapById("##value scale_x").c_str(), &newScaleVal.x, 0.1f);

		ImGui::TableNextColumn();
		ImGui::Text("y: ");
		ImGui::DragFloat(wrapById("##value scale_y").c_str(), &newScaleVal.y, 0.1f);

		ImGui::TableNextColumn();
		ImGui::Text("z: ");
		ImGui::DragFloat(wrapById("##value scale_z").c_str(), &newScaleVal.z, 0.1f);

		ImGui::EndTable();

		ViewEvent event(mContext->getRegistry());
		event.viewEventType = ViewEventType::InputEvent;
		event.name = "properties.scale";
		event.valueType = BindingValueType::Vec3;
		event.value = ToyEngine::RenderHelper::getVec3String(newScaleVal);

		if (oldScaleVal != newScaleVal) {
			mController->addViewEvent(event);
		}
	}
}

void ui::TransfromPanelItem::drawRotationSetting()
{
	glm::vec3 oldRotationVal = mController->getVec("properties.rotation");
	glm::vec3 newRotationVal = oldRotationVal;

	ImGui::Text("ROTATION");
	if (ImGui::BeginTable("axis", 3, ImGuiTableFlags_Borders)) {
		ImGui::TableNextColumn();
		ImGui::Text("pitch: ");
		ImGui::DragFloat(wrapById("##value pitch").c_str(), &newRotationVal.x, 5.0f);


		ImGui::TableNextColumn();
		ImGui::Text("yaw: ");
		ImGui::DragFloat(wrapById("##value yaw").c_str(), &newRotationVal.y, 5.0f);

		ImGui::TableNextColumn();
		ImGui::Text("row: ");
		ImGui::DragFloat(wrapById("##value row").c_str(), &newRotationVal.z, 5.0f);

		ImGui::EndTable();

		ViewEvent event(mContext->getRegistry());
		event.viewEventType = ViewEventType::InputEvent;
		event.name = "properties.rotation";
		event.valueType = BindingValueType::Vec3;
		event.value = ToyEngine::RenderHelper::getVec3String(newRotationVal);

		if (oldRotationVal != newRotationVal) {
			mController->addViewEvent(event);
		}
	}
}

void ui::TransfromPanelItem::drawPositionSetting()
{
	glm::vec3 oldPositionVal = mController->getVec("properties.position");
	glm::vec3 newPositionVal = oldPositionVal;

	ImGui::Text("POSITION");
	if (ImGui::BeginTable("axis", 3, ImGuiTableFlags_Borders)) {
		ImGui::TableNextColumn();
		ImGui::Text("x: ");
		ImGui::DragFloat(wrapById("##value pos_x").c_str(), &newPositionVal.x);

		ImGui::TableNextColumn();
		ImGui::Text("y: ");
		ImGui::DragFloat(wrapById("##value pos_y").c_str(), &newPositionVal.y);

		ImGui::TableNextColumn();
		ImGui::Text("z: ");
		ImGui::DragFloat(wrapById("##value pos_z").c_str(), &newPositionVal.z);

		ImGui::EndTable();

		ViewEvent event(mContext->getRegistry());
		event.viewEventType = ViewEventType::InputEvent;
		event.name = "properties.position";
		event.valueType = BindingValueType::Vec3;
		event.value = ToyEngine::RenderHelper::getVec3String(newPositionVal);

		if (oldPositionVal != newPositionVal) {
			mController->addViewEvent(event);
		}
	}
}
