#pragma once
#include <memory>
#include"UI/Controller/Controller.h"
#include <UI/Model/InspectorPanelModel.h>

namespace ui {
	class InspectorPanelController: public Controller
	{
	public:
		InspectorPanelController(std::unique_ptr<InspectorPanelModel>&& model);

		virtual void registerBindings() override;

	private:
		virtual void onSelectionChange(entt::entity) override;
		
		std::unique_ptr<ui::InspectorPanelModel> mInspectorPanelModel;
	
		entt::registry& mRegistry;
	};
}


