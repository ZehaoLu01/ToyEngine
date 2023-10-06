#include <UI/View/CreatePointLightPanelItem.h>

void ui::CreatePointLightPanelItem::render()
{
	
	PointLightPropsPanelItem::render();
	drawCreatePointLightButton();
}

void ui::CreatePointLightPanelItem::drawCreatePointLightButton()
{
	if (ImGui::Button(wrapById("Add point light").c_str())) {
		ViewEvent event(mContext->getRegistry());
		event.viewEventType = ViewEventType::ButtonEvent;
		event.name = "onCreatePointLightButtonDown";
		event.vectorGroup = { mPosition, mAmbient, mDiffuse, mSpecular};
		event.floatGroup = { constant, linear, quadratic };
		mController->addViewEvent(event);
	}
}
