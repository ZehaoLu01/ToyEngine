#pragma once
#include <memory>
#include"UI/Controller/Controller.h"
#include <UI/Model/PropertiesScreenModel.h>
#include <entt/entt.hpp>

namespace ui {
	class PropertiesScreenController: public Controller, public std::enable_shared_from_this<PropertiesScreenController>
	{
	public:
		PropertiesScreenController(entt::registry& registry);

		virtual void registerBindings() override;

	private:
		std::shared_ptr<ui::PropertiesScreenModel> mPropertiesScreenModel;

		entt::registry& mRegistry;
	};
}


