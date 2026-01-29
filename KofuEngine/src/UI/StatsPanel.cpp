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

	ImGui::Text(("FPS - %d"), statHelp.GetFPS());
	ImGui::Text(("Delta Time - %.3f ms"), statHelp.GetDeltaMS());
	ImGui::Text(("Total Vertices - %d"), statHelp.GetTotalVertexCount(activeScene->meshes));
	ImGui::Text(("Total Indices - %d"), statHelp.GetTotalIndexCount(activeScene->meshes));
	ImGui::Text(("Total Triangles - %d"), statHelp.GetTotalTriangleCount(activeScene->meshes));
	ImGui::Text(("Draw Calls - %d"), statHelp.GetDrawCallCount());

	ImGui::End();
}
