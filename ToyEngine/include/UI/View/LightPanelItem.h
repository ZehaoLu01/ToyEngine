#pragma once
#include "UI/View/PanelItem.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <UI/Controller/Controller.h>
#include <UI/View/ImGuiManager.h>

namespace ui {
    class LightPanelItem :
        public PanelItem
    {
    public:
        virtual void renderContent()=0;
        using PanelItem::PanelItem;
    protected:
        void drawAmbientPicker();
        void drawDiffusePicker();
        void drawSpecularPicker();
        void drawCoefficientSetting();

        glm::vec3 mAmbient = { 0.0f, 0.0f, 0.0f };
        glm::vec3 mDiffuse = { 0.0f, 0.0f, 0.0f };
        glm::vec3 mSpecular = { 0.0f, 0.0f, 0.0f };
        float constant = 1.0f;
        float linear = 0.09f;
        float quadratic = 0.032f;

    };
}


