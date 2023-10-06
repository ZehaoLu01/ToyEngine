#include "UI/View/PanelItem.h"
namespace ui{

	PanelItem::PanelItem(std::function<bool(ImGuiContext*)> condition, std::shared_ptr<Controller> controller, ImGuiContext* context)
		: mCondition(condition), mController(controller), mContext(context)
	{
		counter++;
		mId = counter;
	}

	int PanelItem::counter = 0;
}
