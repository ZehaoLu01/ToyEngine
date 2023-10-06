#pragma once
#include <UI/View/LightPanelItem.h>

namespace ui {
	class PointLightPropsPanelItem :
		public LightPanelItem
	{
	public:
		LightPanelItem::LightPanelItem;

		// Inherited via LightPanelItem
		virtual void renderContent() override;
	protected:
		void drawPositionSetting();

		glm::vec3 mPosition = { 0,0,0 };
	};
}

