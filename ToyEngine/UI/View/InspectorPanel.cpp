#include <glm/fwd.hpp>
#include <ImGuIZMO/imGuIZMOquat.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <UI/View/ImGuiManager.h>
#include <UI/View/InspectorPanel.h>
#include <UI/Controller/InspectorPanelController.h>
#include <UI/View/DirectionalLightPropsPanelItem.h>
#include <UI/View/PointLightPropsPanelItem.h>
#include <UI/View/TransfromPanelItem.h>
#include <UI/View/PointLightPropsPanelItem.h>
#include <UI/View/CreateDirectionalLightPanelItem.h>
#include <UI/View/CreatePointLightPanelItem.h>

namespace ui {
	void InspectorPanel::render() {
		ImGui::Begin("Renderer Settings", nullptr);

		//if (mContext->getSelectedEntity() != entt::null) {
		//	renderObjectPropertyMenu();
		//}

		//renderCreateLightingMenu();
		for (const auto& panelItem : panelItems) {
			if (panelItem->shouldRender()) {
				panelItem->render();
			}
		}

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	void InspectorPanel::registerPanelItems() {
		registerPanelItem<TransfromPanelItem>([](ImGuiContext* context) {
			entt::entity selected = context->getSelectedEntity();
			if (selected == entt::null) {
				return false;
			}
			else {
				return true;
			}
		});

		registerPanelItem<DirectionalLightPropsPanelItem>([](ImGuiContext* context) {
			entt::entity selected = context->getSelectedEntity();
			if (selected == entt::null) {
				return false;
			}

			auto lightComp = context->getRegistry().try_get<ToyEngine::LightComponent>(selected);
			if (!lightComp || lightComp->type != "directional") {
				return false;
			}

			return true;
		});


		registerPanelItem<PointLightPropsPanelItem>([](ImGuiContext* context) {
			entt::entity selected = context->getSelectedEntity();
			if (selected == entt::null) {
				return false;
			}

			auto lightComp = context->getRegistry().try_get<ToyEngine::LightComponent>(selected);
			if (!lightComp || lightComp->type != "point") {
				return false;
			}

			return true;
		});

		//TODO: move create light items to another individual panel.

		registerPanelItem<CreatePointLightPanelItem>([](ImGuiContext*) {
			return true;
		});

		registerPanelItem<CreateDirectionalLightPanelItem>([](ImGuiContext*) {
			return true;
		});
	}
}
