#pragma once
#include "ViewportPanel.h"
#include <imgui.h>
#include <glad/glad.h>
#include "rendering/Scene.h"

void ViewportPanel::RenderUI(Scene* activeScene)
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("Viewport");
	
	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

	if ((viewportPanelSize.x != viewportSize.x || viewportPanelSize.y != viewportSize.y) && !ImGui::IsMouseDragging(0))
	{
		viewportSize = viewportPanelSize;
		activeScene->msaaSceneFBO.Resize((int)viewportSize.x, (int)viewportSize.y);
		activeScene->ppFBO.Resize((int)viewportSize.x, (int)viewportSize.y);
	}

	GLuint textureID = activeScene->ppFBO.colorTex;
	ImGui::Image((void*)textureID, viewportSize, ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));

	ImGui::End();
	ImGui::PopStyleVar();
}
