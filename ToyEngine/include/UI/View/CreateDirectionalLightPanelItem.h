#pragma once
#include <UI/View/DirectionalLightPropsPanelItem.h>
namespace ui {
    class CreateDirectionalLightPanelItem : public DirectionalLightPropsPanelItem
    {
    public:
        DirectionalLightPropsPanelItem::DirectionalLightPropsPanelItem;
        virtual void renderContent();
    private:
        void drawCreateDirectionalLightButton();
    };

}


