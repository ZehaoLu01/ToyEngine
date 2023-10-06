#include "UI/View/LightPanelItem.h"

void ui::LightPanelItem::drawAmbientPicker()
{
	ImGui::Text("Ambient");
	ImGui::ColorEdit4(wrapById("ambient").c_str(), (float*)&mAmbient, ImGuiColorEditFlags_DisplayRGB);
}

void ui::LightPanelItem::drawDiffusePicker()
{
	ImGui::Text("Diffuse");
	ImGui::ColorEdit4(wrapById("diffuse").c_str(), (float*)&mDiffuse, ImGuiColorEditFlags_DisplayRGB);
}

void ui::LightPanelItem::drawSpecularPicker()
{
	ImGui::Text(("Specular"));
	ImGui::ColorEdit4(wrapById("specular").c_str(), (float*)&mSpecular, ImGuiColorEditFlags_DisplayRGB);
}

void ui::LightPanelItem::drawCoefficientSetting()
{
	ImGui::Text("Coefficients");
	if (ImGui::BeginTable("axis", 3, ImGuiTableFlags_Borders)) {
		ImGui::TableNextColumn();
		ImGui::Text("constants: ");
		ImGui::DragFloat(wrapById("constant").c_str(), &constant, 0.1f);

		ImGui::TableNextColumn();
		ImGui::Text("linear: ");
		ImGui::DragFloat(wrapById("linear").c_str(), &linear, 0.1f);

		ImGui::TableNextColumn();
		ImGui::Text("quadratic: ");
		ImGui::DragFloat(wrapById("quadratic").c_str(), &quadratic, 0.1f);

		ImGui::EndTable();
	}
}
