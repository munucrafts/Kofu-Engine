#pragma once
#include "rendering/Scene.h"
#include "OutlinerPanel.h"
#include <imgui.h>

void OutlinerPanel::RenderUI(Scene* activeScene)
{
	ImGui::Begin("Outliner");

	if (ImGui::TreeNode("Meshes"))
	{
		for (int i = 0; i < activeScene->meshes.size(); i++)
		{
			std::string name = "Mesh " + std::to_string(i);
			ImGui::Button(name.c_str(), ImVec2(ImVec2(ImGui::GetContentRegionAvail().x, 0.0f)));
		}

		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Lights"))
	{
		for (int i = 0; i < activeScene->lights.size(); i++)
		{
			std::string name = "Light " + std::to_string(i);
			ImGui::Button(name.c_str(), ImVec2(ImVec2(ImGui::GetContentRegionAvail().x, 0.0f)));
		}

		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Camera"))
	{
		for (int i = 0; i < activeScene->meshes.size(); i++)
		{
			std::string name = "Camera " + std::to_string(i);
			ImGui::Button(name.c_str(), ImVec2(ImVec2(ImGui::GetContentRegionAvail().x, 0.0f)));
		}

		ImGui::TreePop();
	}

	ImGui::End();
}
