#pragma once
#include <memory>
#include"UI/Controller/Controller.h"
#include <UI/Model/PropertiesScreenModel.h>

namespace ui {
	class PropertiesScreenController: public Controller
	{
	public:
		PropertiesScreenController(entt::registry& registry);

		virtual void registerBindings() override;

	private:
		virtual void onSelectionChange(entt::entity) override;

		
		std::shared_ptr<ui::PropertiesScreenModel> mPropertiesScreenModel;
	
		entt::registry& mRegistry;
	};
}


