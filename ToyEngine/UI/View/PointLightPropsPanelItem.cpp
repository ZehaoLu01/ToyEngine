#include <UI/View/PointLightPropsPanelItem.h>

void ui::PointLightPropsPanelItem::renderContent()
{
	drawPositionSetting();
	drawAmbientPicker();
	drawDiffusePicker();
	drawSpecularPicker();
}

void ui::PointLightPropsPanelItem::drawPositionSetting()
{
	ImGui::Text("Position");
	if (ImGui::BeginTable("axis", 3, ImGuiTableFlags_Borders)) {
		ImGui::TableNextColumn();
		ImGui::Text("x: ");
		ImGui::DragFloat(wrapById("##value x").c_str(), &mPosition.x, 0.1f);

		ImGui::TableNextColumn();
		ImGui::Text("y: ");
		ImGui::DragFloat(wrapById("##value y").c_str(), &mPosition.y, 0.1f);

		ImGui::TableNextColumn();
		ImGui::Text("z: ");
		ImGui::DragFloat(wrapById("##value z").c_str(), &mPosition.z, 0.1f);

		ImGui::EndTable();
	}
}
