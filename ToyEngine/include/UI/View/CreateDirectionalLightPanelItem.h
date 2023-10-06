#pragma once
#include <UI/View/DirectionalLightPropsPanelItem.h>
namespace ui {
    class CreateDirectionalLightPanelItem : public DirectionalLightPropsPanelItem
    {
    public:
        DirectionalLightPropsPanelItem::DirectionalLightPropsPanelItem;
        virtual void render();
    private:
        void drawCreateDirectionalLightButton();
    };

}


