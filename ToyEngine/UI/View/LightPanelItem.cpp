#include "UI/View/LightPanelItem.h"

void ui::LightPanelItem::drawAmbientPicker()
{
	ImGui::Text("Ambient");
	ImGui::ColorEdit4(wrapById("point_ambient").c_str(), (float*)&mAmbient, ImGuiColorEditFlags_DisplayRGB);
}

void ui::LightPanelItem::drawDiffusePicker()
{
	ImGui::Text(wrapById("Diffuse").c_str());
	ImGui::ColorEdit4(wrapById("point##2").c_str(), (float*)&mDiffuse, ImGuiColorEditFlags_DisplayRGB);
}

void ui::LightPanelItem::drawSpecularPicker()
{
	ImGui::Text(("Specular"));
	ImGui::ColorEdit4(wrapById("point##3").c_str(), (float*)&mSpecular, ImGuiColorEditFlags_DisplayRGB);
}

void ui::LightPanelItem::drawCoefficientSetting()
{
	ImGui::Text("Coefficients");
	if (ImGui::BeginTable("axis", 3, ImGuiTableFlags_Borders)) {
		ImGui::TableNextColumn();
		ImGui::Text("constants: ");
		ImGui::DragFloat(wrapById("##value x").c_str(), &constant, 0.1f);

		ImGui::TableNextColumn();
		ImGui::Text("linear: ");
		ImGui::DragFloat(wrapById("##value y").c_str(), &linear, 0.1f);

		ImGui::TableNextColumn();
		ImGui::Text("quadratic: ");
		ImGui::DragFloat(wrapById("##value z").c_str(), &quadratic, 0.1f);

		ImGui::EndTable();
	}
}
