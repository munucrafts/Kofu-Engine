#pragma once
#include "rendering/Scene.h"
#include "DetailsPanel.h"
#include <imgui.h>

void DetailsPanel::RenderUI(Scene* activeScene)
{
	ImGui::Begin("Details");

	if (activeScene->selectedObject == nullptr || activeScene->selectedObject->objectID == "None")
	{
		ImGui::Text("No Selection");
		ImGui::End();
		return;
	}



	ImGui::End();
}
