#pragma once
#include "ViewportPanel.h"
#include <imgui.h>
#include <glad/glad.h>
#include "rendering/Scene.h"
#include <utilities/Util.h>

void ViewportPanel::RenderUI(Scene* activeScene)
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("Viewport");

	RenderRenderModeUI(activeScene->renderMode);

	mouseHovering = ImGui::IsWindowHovered();

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

bool ViewportPanel::IsMouseHoveringOnViewport()
{
	return mouseHovering;
}

void ViewportPanel::RenderRenderModeUI(RenderMode& renderMode)
{
    std::string currentModeText = Util::EnumToString(renderMode);
    const char* renderModeTexts[] = { "Lit", "Unlit", "Depth", "Normal" };
    RenderMode modes[] = { LIT, UNLIT, DEPTH, NORMAL };

	ImGui::SetNextItemWidth(100.0f);
    if (ImGui::BeginCombo("Render Modes", currentModeText.c_str()))
    {
        for (int i = 0; i < IM_ARRAYSIZE(renderModeTexts); i++)
        {
            bool isSelected = (renderMode == modes[i]);

            if (ImGui::Selectable(renderModeTexts[i], isSelected))
            {
                renderMode = modes[i];
            }

            if (isSelected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }
}

