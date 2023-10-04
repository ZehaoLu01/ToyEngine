#include "UI/View/SceneHierarchyPanel.h"
#include<queue>

namespace ui {
	using ToyEngine::TagComponent;
	using ToyEngine::RelationComponent;

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
				mSelectionContext = entt::null;
		}
		ImGui::End();
	}

	void SceneHierarchyPanel::hierarchyTraversal(entt::registry& registry, entt::entity head)
	{
		if (head == entt::null) {
			return;
		}
		const auto& [currentTagComp, currentRelationComp] = registry.get<TagComponent, RelationComponent>(head);

		auto tag = currentTagComp.name;

		ImGuiTreeNodeFlags flags = ((mSelectionContext == head) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
		if (currentRelationComp.children.size() == 0) {
			flags |= ImGuiTreeNodeFlags_Leaf;
		}

		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)head, flags, tag.c_str());

		if (ImGui::IsItemClicked())
		{
			mSelectionContext = head;
			mSelectEntityCallback(head);
		}

		if (opened)
		{
			//ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
			//bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
			//if (opened)
			//	ImGui::TreePop();
			//ImGui::TreePop();
			for (const auto child : currentRelationComp.children) {
				hierarchyTraversal(registry, child);
			}
			ImGui::TreePop();
		}
	}
}
