#include <UI/View/CreateDirectionalLightPanelItem.h>

void ui::CreateDirectionalLightPanelItem::render()
{
	DirectionalLightPropsPanelItem::render();
	drawCreateDirectionalLightButton();
}

void ui::CreateDirectionalLightPanelItem::drawCreateDirectionalLightButton()
{
	if (ImGui::Button(wrapById("Add directional light").c_str())) {
		ViewEvent event(mContext->getRegistry());
		event.viewEventType = ViewEventType::ButtonEvent;
		event.name = "onCreateDirctionalLightButtonDown";
		event.vectorGroup = { mDirection, mAmbient, mDiffuse, mSpecular};
		event.floatGroup = { constant, linear, quadratic };
		mController->addViewEvent(event);
	}
}
