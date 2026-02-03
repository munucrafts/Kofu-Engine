#pragma once
#include "SettingsPanel.h"
#include "rendering/Scene.h"
#include <string>
#include <utilities/Util.h>
#include <imgui.h>
#include <Engine.h>


void SettingsPanel::RenderUI(Scene* activeScene)
{
    ImGui::Begin("Settings");

    static bool vsyncState = true;

    if (ImGui::Checkbox("Enable VSync", &vsyncState)) 
        Engine::GetEngine().EnableVSync(vsyncState);

    RenderMode& renderMode = activeScene->renderMode;
    std::string currentModeText = Util::EnumToString(renderMode);

    const char* renderModeTexts[] = { "Lit", "Unlit", "Depth", "Normal" };
    RenderMode modes[] = { LIT, UNLIT, DEPTH, NORMAL };

    ImGui::Text("Render Mode");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);

    if (ImGui::BeginCombo("##RenderModes", currentModeText.c_str()))
    {
        for (int i = 0; i < 4; i++)
        {
            if (ImGui::Selectable(renderModeTexts[i], renderMode == modes[i]))
            {
                renderMode = modes[i];
            }
        }

        ImGui::EndCombo();
    }

    ImGui::End();
}
