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
	ImGui::Text(("Vertices - %d"), statHelp.GetVertexCount(activeScene->meshes));
	ImGui::Text(("Indices - %d"), statHelp.GetIndexCount(activeScene->meshes));
	ImGui::Text(("Triangles - %d"), statHelp.GetTriangleCount(activeScene->meshes));
	ImGui::Text(("Draw Calls - %d"), statHelp.GetDrawCallCount());

	ImGui::End();
}
