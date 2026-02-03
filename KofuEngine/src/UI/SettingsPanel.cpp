#pragma once
#include "SettingsPanel.h"
#include "rendering/Scene.h"
#include <string>
#include <utilities/Util.h>
#include <imgui.h>


void SettingsPanel::RenderUI(Scene* activeScene)
{
    ImGui::Begin("Settings");

    RenderMode& renderMode = activeScene->renderMode;

    std::string currentModeText = Util::EnumToString(renderMode);
    const unsigned int numModes = 4;
    const char* renderModeTexts[numModes] = { "Lit", "Unlit", "Depth", "Normal" };
    RenderMode modes[numModes] = { LIT, UNLIT, DEPTH, NORMAL };

    float itemWidth = 100.0f;
    float posX = ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x - itemWidth;

    ImGui::SetCursorPosX(posX);
    ImGui::SetNextItemWidth(itemWidth);

    if (ImGui::BeginCombo("##RenderModes", currentModeText.c_str()))
    {
        for (int i = 0; i < numModes; i++)
        {
            bool isSelected = (renderMode == modes[i]);
            if (ImGui::Selectable(renderModeTexts[i], isSelected))
            {
                renderMode = modes[i];
            }
            if (isSelected) ImGui::SetItemDefaultFocus();
        }

        ImGui::EndCombo();
    }

    ImGui::End();
}

