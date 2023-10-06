#pragma once
#include <functional>
#include <entt/entt.hpp>
#include <string>
#include <imgui.h>

namespace ui {
	class ImGuiContext;
	class Controller;
	using PanelItemPredicate = std::function<bool(ImGuiContext*)>;

	class PanelItem
	{
	public:
		void render() {
			if(ImGui::TreeNode(name.c_str())) {
				renderContent();
				ImGui::TreePop();
			}	
		}
		virtual void renderContent() = 0;
		
		PanelItem() = delete;
		PanelItem(const std::string& name, PanelItemPredicate condition, std::shared_ptr<Controller> controller, ImGuiContext* context);
		
		bool shouldRender() {
			return mCondition(mContext);
		}
	protected:
		int getId() {
			return mId;
		}

		std::string getIdStr() {
			return "##" + std::to_string(mId);
		}

		// Used to wrap the label of interactable ImGui wighets to avoid collision.
		std::string wrapById(const char* c_str) {
			return std::string(c_str) + std::string(" ") + getIdStr();
		}

		PanelItemPredicate mCondition;
		std::shared_ptr<Controller> mController;
		ImGuiContext* mContext;
	private:
		std::string name;
		static int counter;
		int mId;
	};
}


