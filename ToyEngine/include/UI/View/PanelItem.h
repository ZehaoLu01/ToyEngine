#pragma once
#include <functional>
#include <entt/entt.hpp>
#include "ImGuiManager.h"

namespace ui {
	class PanelItem
	{
	public:
		virtual void render() = 0;
		PanelItem() = delete;
		PanelItem(std::function<bool(ImGuiContext*)> condition, std::shared_ptr<Controller> controller, ImGuiContext* context);
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

		std::function<bool(ImGuiContext*)> mCondition;
		std::shared_ptr<Controller> mController;
		ImGuiContext* mContext;
	private:
		static int counter;
		int mId;
	};
}


