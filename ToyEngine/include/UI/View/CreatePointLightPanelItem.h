#pragma once
#include <UI/View/PointLightPropsPanelItem.h>

namespace ui{

	class CreatePointLightPanelItem: public PointLightPropsPanelItem
	{
	public:
		PointLightPropsPanelItem::PointLightPropsPanelItem;
		virtual void renderContent();
	private:
		void drawCreatePointLightButton();
	};
}
