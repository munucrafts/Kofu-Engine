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
	int& viewWidth = activeScene->viewportWidth;
	int& viewHeight = activeScene->viewportHeight;

	if ((viewportPanelSize.x != viewWidth || viewportPanelSize.y != viewHeight) && !ImGui::IsMouseDragging(0))
	{
		viewWidth = (int)viewportPanelSize.x;
		viewHeight = (int)viewportPanelSize.y;

		activeScene->msaaSceneFBO.Resize(viewWidth, viewHeight);
		activeScene->ppFBO.Resize(viewWidth, viewHeight);
	}

	GLuint textureID = activeScene->ppFBO.colorTex;
	ImGui::Image((void*)textureID, ImVec2((float)viewWidth, (float)viewHeight), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));

	ImGui::End();
	ImGui::PopStyleVar();
}