#pragma once
#include "StatsPanel.h"
#include <imgui.h>
#include <Stats/StatsHelper.h>
#include "iostream"
#include "string"
#include "rendering/Scene.h"

void StatsPanel::RenderUI(Scene* activeScene)
{
	StatsHelper& statHelp = StatsHelper::GetStatsHelper();

	ImGui::Begin("Statistics");

	ImGui::Text(("FPS - " + std::to_string(statHelp.GetFPS())).c_str());
	ImGui::Text(("Delta Time - " + std::to_string(statHelp.GetDeltaMS())).c_str());
	ImGui::Text(("Vertices - " + std::to_string(statHelp.GetVertexCount(activeScene->meshes))).c_str());
	ImGui::Text(("Indices - " + std::to_string(statHelp.GetIndexCount(activeScene->meshes))).c_str());
	ImGui::Text(("Triangles - " + std::to_string(statHelp.GetTriangleCount(activeScene->meshes))).c_str());

	ImGui::End();
}
