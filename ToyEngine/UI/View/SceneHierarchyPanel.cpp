#include "UI/View/SceneHierarchyPanel.h"
#include "UI/View/ImGuiManager.h"
#include<queue>

namespace ui {
	using ToyEngine::TagComponent;
	using ToyEngine::RelationComponent;

	SceneHierarchyPanel::SceneHierarchyPanel(std::shared_ptr<ToyEngine::Scene> scene, ImGuiContext* context, std::shared_ptr<SceneHierarchyController> controller, std::function<void(entt::entity)> onSelect) :SceneHierarchyPanel(scene, context, controller)
	{
		mSelectEntityCallback = onSelect;
	}

	void SceneHierarchyPanel::render()
	{
		auto& registry = mScene->getRegistry();

		ImGui::Begin("Scene Hierarchy");

		// TODO: use controller here!!
		if (mScene)
		{
			auto entities = registry.view <TagComponent, RelationComponent> ();

			for (auto entity : entities)
			{
				// TODO: remove tag?
				const auto& [tagComp, relationComp]= entities.get<TagComponent, RelationComponent>(entity);

				// We only want to begin from top of the hierarchy tree;
				if (relationComp.parent != entt::null && relationComp.parent!=mScene->getRootEntity()) {
					continue;
				}

				hierarchyTraversal(registry, entity);
			};

			if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
				setSelected(entt::null);
		}
		ImGui::End();
	}

	entt::entity SceneHierarchyPanel::getSelectedEntity() const
	{
		return mContext->selectedEntity;
	}

	void SceneHierarchyPanel::hierarchyTraversal(entt::registry& registry, entt::entity head)
	{
		if (head == entt::null) {
			return;
		}
		const auto& [currentTagComp, currentRelationComp] = registry.get<TagComponent, RelationComponent>(head);

		auto tag = currentTagComp.name;

		ImGuiTreeNodeFlags flags = ((mContext->selectedEntity == head) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
		if (currentRelationComp.children.size() == 0) {
			flags |= ImGuiTreeNodeFlags_Leaf;
		}
		
		// TreeDepth++
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)head, flags, tag.c_str());

		if (ImGui::IsItemClicked())
		{
			setSelected(head);
		}

		if (opened)
		{
			for (const auto child : currentRelationComp.children) {
				hierarchyTraversal(registry, child);
			}
			// TreeDepth--
			ImGui::TreePop();
		}
	}

	void SceneHierarchyPanel::setSelected(entt::entity entity)
	{
		mSelectEntityCallback(entity);
		mContext->selectedEntity = entity;
	}
}
