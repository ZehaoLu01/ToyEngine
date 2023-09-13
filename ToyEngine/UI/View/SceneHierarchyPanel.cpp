#include "UI/View/SceneHierarchyPanel.h"

namespace ui {
	void SceneHierarchyPanel::tick()
	{
		ImGui::Begin("Scene Hierarchy");


		// TODO: use controller here!!
		if (mScene)
		{
			auto entities = mScene->getRegistry().view<ToyEngine::TagComponent>();

			for (auto entity : entities)
			{
				auto& tag = mScene->getRegistry().get<ToyEngine::TagComponent>(entity).name;

				ImGuiTreeNodeFlags flags = ((mSelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
				flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
				bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
				if (ImGui::IsItemClicked())
				{
					mSelectionContext = entity;
					mSelectEntityCallback(entity);
				}

				bool entityDeleted = false;
				if (ImGui::BeginPopupContextItem())
				{
					if (ImGui::MenuItem("Delete Entity"))
						entityDeleted = true;

					ImGui::EndPopup();
				}

				if (opened)
				{
					ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
					bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
					if (opened)
						ImGui::TreePop();
					ImGui::TreePop();
				}

				if (entityDeleted)
				{
					//m_Context->DestroyEntity(entity);
					//if (m_SelectionContext == entity)
					//	m_SelectionContext = {};
				}
			};

			if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
				mSelectionContext = entt::null;
		}
		ImGui::End();
	}
	void SceneHierarchyPanel::setOnSelectCallBack(std::function<void(entt::entity)>)
	{
	}
}
