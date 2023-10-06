#include <ImGuIZMO/imGuIZMOquat.h>
#include <UI/View/DirectionalLightPropsPanelItem.h>

void ui::DirectionalLightPropsPanelItem::renderContent()
{
	drawDirectionSetting();
	drawAmbientPicker();
	drawDiffusePicker();
	drawSpecularPicker();
}

void ui::DirectionalLightPropsPanelItem::drawDirectionSetting()
{
	ImGui::Text("Direction");
	// I assume, for a vec3, a direction starting from origin, so if you use a vec3 to identify
	// a light spot toward origin need to change direction
	// or explicitly
	vec3 vgmLightDir = { mDirection.x, mDirection.y, mDirection.z };
	if (ImGui::gizmo3D("", vgmLightDir, 300, imguiGizmo::modeDirection)) {
		mDirection = { vgmLightDir.x, vgmLightDir.y, vgmLightDir.z };
	}
}
