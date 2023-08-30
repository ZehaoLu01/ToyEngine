#include"UI/Model/PropertiesScreenModel.h"

ui::PropertiesScreenModel::PropertiesScreenModel(entt::registry& registry):mRegistry(registry)
{
}

ui::PropertiesScreenModel::PropertiesScreenModel(entt::registry& registry, std::vector<std::shared_ptr<ToyEngine::RenderComponent>> defaultSelectedComponents) :mRegistry(registry), mSelectedRenderComponents(defaultSelectedComponents) {};
