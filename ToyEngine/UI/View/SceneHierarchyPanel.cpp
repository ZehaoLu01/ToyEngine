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
		return mContext->getSelectedEntity();
	}

	void SceneHierarchyPanel::hierarchyTraversal(entt::registry& registry, entt::entity head)
	{
		if (head == entt::null) {
			return;
		}
		const auto& [currentTagComp, currentRelationComp] = registry.get<TagComponent, RelationComponent>(head);

		auto tag = currentTagComp.name;

		ImGuiTreeNodeFlags flags = ((mContext->getSelectedEntity() == head) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
		if (currentRelationComp.children.size() == 0) {
			flags |= ImGuiTreeNodeFlags_Leaf;
		}
		
		// TreeDepth++
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)head, flags, tag.c_str());
		if (ImGui::BeginPopupContextItem()) // <-- This is using IsItemHovered()
		{
			// Select tree node if it is right clicked.
			if (mContext->getSelectedEntity() != head) {
				mContext->setSelectedEntity(head);
			}

			if (ImGui::MenuItem("Delete entity")) {
				entt::entity selected = mContext->getSelectedEntity();

				ViewEvent event(mScene->getRegistry());
				event.viewEventType = ViewEventType::ButtonEvent;
				event.name = "onDeleteEnittyButtonDown";
				event.value = std::to_string(static_cast<int>(selected));
				mController->addViewEvent(event);

			}
			ImGui::EndPopup();
		}

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
		//TODO: remove this because I don't think I should make copies of one state everywhere!
		//if (entity != entt::null) {
		//	mSelectEntityCallback(entity);
		//}

		mContext->setSelectedEntity(entity);
	}
}
