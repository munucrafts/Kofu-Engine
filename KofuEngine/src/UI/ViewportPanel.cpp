#pragma once
#include "ViewportPanel.h"
#include <imgui.h>
#include <glad/glad.h>
#include "rendering/Scene.h"

void ViewportPanel::RenderUI(Scene* activeScene)
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("Viewport");
	
	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	int& viewWidth = activeScene->viewportWidth;
	int& viewHeight = activeScene->viewportHeight;

	if ((viewportPanelSize.x != viewWidth || viewportPanelSize.y != viewHeight) && !ImGui::IsMouseDragging(0))
	{
		viewWidth = (int)viewportPanelSize.x;
		viewHeight = (int)viewportPanelSize.y;
		activeScene->ResizeFBOs(viewWidth, viewHeight);
	}


	GLuint textureID = activeScene->screenTexFBO.colorTex;
	ImGui::Image((void*)(intptr_t)textureID, ImVec2((float)viewWidth, (float)viewHeight), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));

	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar();
}