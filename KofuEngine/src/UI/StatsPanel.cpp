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

	std::vector<Mesh*> meshes = activeScene->meshes;

	ImGui::Text(("FPS - %d"), statHelp.GetFPS());
	ImGui::Text(("Delta Time - %.3f ms"), statHelp.GetDeltaMS());
	ImGui::Text(("Total Meshes - %d"), meshes.size());
	ImGui::Text(("Total Vertices - %d"), statHelp.GetTotalVertexCount(meshes));
	ImGui::Text(("Total Indices - %d"), statHelp.GetTotalIndexCount(meshes));
	ImGui::Text(("Total Triangles - %d"), statHelp.GetTotalTriangleCount(meshes));
	ImGui::Text(("Draw Calls - %d"), statHelp.GetDrawCallCount());

	ImGui::End();
}
