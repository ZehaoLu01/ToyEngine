#pragma once
#include <memory>
#include"UI/Controller/Controller.h"
#include <UI/Model/PropertiesScreenModel.h>

namespace ui {
	class PropertiesScreenController: public Controller
	{
	public:
		PropertiesScreenController(std::unique_ptr<PropertiesScreenModel>&& model);

		virtual void registerBindings() override;

	private:
		virtual void onSelectionChange(entt::entity) override;
		
		std::unique_ptr<ui::PropertiesScreenModel> mPropertiesScreenModel;
	
		entt::registry& mRegistry;
	};
}


