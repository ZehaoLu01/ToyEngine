#pragma once
#include "UI/View/LightPanelItem.h"

namespace ui{
	class DirectionalLightPropsPanelItem :
		public LightPanelItem
	{
	public:
		LightPanelItem::LightPanelItem;
		virtual void renderContent();
	protected:
		void drawDirectionSetting();

		glm::vec3 mDirection = {-1.0f, -1.0f, -1.0f};
	};
}

