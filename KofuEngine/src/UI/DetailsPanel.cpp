#pragma once
#include "rendering/Scene.h"
#include "DetailsPanel.h"
#include "Components/Components.h"
#include <imgui.h>
#include <utilities/Util.h>
#include "TransformPanel.h"

void DetailsPanel::RenderUI(Scene* activeScene)
{
	ImGui::Begin("Details");

	if (activeScene->selectedObject == nullptr || activeScene->selectedObject->objectID == "None")
	{
		ImGui::Text("No Selection");
		ImGui::End();
		return;
	}

	ObjectType objType = activeScene->selectedObject->objectType;
	std::string objIDText = "Object ID : " + activeScene->selectedObject->objectID;
	std::string objTypeText = "Object Type : " + Util::EnumToString(objType);

	ImVec4 normalColor = ImGui::GetStyleColorVec4(ImGuiCol_Button);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, normalColor);
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, normalColor);

	ImGui::Button(objIDText.c_str());
	ImGui::Button(objTypeText.c_str());

	ImGui::PopStyleColor(2);

	TransformPanel transformPanel;
	transformPanel.RenderUI();

	switch (objType)
	{
		case(STATIC_MESH):
		{

		}
		case(INSTANCED_STATIC_MESH) :
		{

		}
		case(SKELETAL_MESH):
		{

		}
		case(SKY_BOX):
		{

		}
		case(CAMERA):
		{

		}
		case(DIRECTIONAL_LIGHT):
		{

		}
		case(SPOT_LIGHT):
		{

		}
		case(POINT_LIGHT):
		{

		}
	}

	ImGui::End();
}
