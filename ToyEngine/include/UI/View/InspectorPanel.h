#pragma once
#include <memory>
#include <functional>

#include <entt/entt.hpp>
#include <UI/View/PanelItem.h>

namespace ToyEngine{
	class Scene;
}

namespace ui {
	class InspectorPanelController;
	class PanelItem;
	class ImGuiContext;
	using PanelItemPredicate = std::function<bool(ImGuiContext*)>;

	class InspectorPanel
	{
	public:
		InspectorPanel() = default;
		InspectorPanel(std::shared_ptr<ToyEngine::Scene> scene, ImGuiContext* context, std::shared_ptr<InspectorPanelController> controller) :mScene(scene), mInspectorPanelController(controller), mContext(context) {
			registerPanelItems();
		};
		void render();
	private:
		void renderObjectPropertyMenu();
		void renderCreateLightingMenu();
		void drawPositionProps();
		void drawRotationProps();
		void drawScaleProps();
		//void drawPointlightProps(bool showCreateButton);
		//void drawDirectionalLightProps(bool showCreateButton);
		
		void registerPanelItems();
		template<typename T>
		void registerPanelItem(PanelItemPredicate predicate) {
			//https://stackoverflow.com/questions/2012950/c-class-template-of-specific-baseclass
			static_assert(std::is_base_of<PanelItem, T>::value, "Must be derived from PanelItem");
			panelItems.push_back(std::make_unique<T>(predicate, mInspectorPanelController, mContext));
		}

		std::shared_ptr<InspectorPanelController> mInspectorPanelController;
		std::shared_ptr<ToyEngine::Scene> mScene;
		ImGuiContext* mContext;
		std::vector<std::unique_ptr<PanelItem>> panelItems;
	};

}
