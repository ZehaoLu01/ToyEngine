#pragma once
#include <UI/View/PanelItem.h>

namespace ui {
	
	class TransfromPanelItem :
		public PanelItem
	{
	public:
		using PanelItem::PanelItem;
		virtual void render();

	private:
		void drawScaleSetting();
		void drawRotationSetting();
		void drawPositionSetting();
	};
}

