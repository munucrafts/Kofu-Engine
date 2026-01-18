#pragma once
#include "rendering/Scene.h"
#include "OutlinerPanel.h"
#include <imgui.h>

void OutlinerPanel::RenderUI(Scene* activeScene)
{
    ImGui::Begin("Outliner");

    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.0f, 0.5f));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 1.0f));

    if (ImGui::TreeNode("Meshes"))
    {
        for (int i = 0; i < activeScene->meshes.size(); i++)
        {
            std::string name = "Mesh " + std::to_string(i);
            ImGui::Button(name.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 0.0f));
        }
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Lights"))
    {
        for (int i = 0; i < activeScene->lights.size(); i++)
        {
            std::string name = "Light " + std::to_string(i);
            ImGui::Button(name.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 0.0f));
        }
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Cameras"))
    {
        std::string name = "Camera 0";
        ImGui::Button(name.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 0.0f));
        ImGui::TreePop();
    }

    ImGui::PopStyleVar(2);
    ImGui::End();
}
