#include "UI/View/PanelItem.h"
namespace ui{

	PanelItem::PanelItem(const std::string& name, PanelItemPredicate condition, std::shared_ptr<Controller> controller, ImGuiContext* context)
		: name(name), mCondition(condition), mController(controller), mContext(context)
	{
		counter++;
		mId = counter;
	}

	int PanelItem::counter = 0;
}
