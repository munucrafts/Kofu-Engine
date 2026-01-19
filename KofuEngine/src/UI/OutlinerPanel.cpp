#pragma once
#include "rendering/Scene.h"
#include "OutlinerPanel.h"
#include <imgui.h>
#include "geometry/Object.h"

void OutlinerPanel::RenderUI(Scene* activeScene)
{
    ImGui::Begin("Outliner");

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

    if (ImGui::TreeNode("Meshes"))
    {
        for (int i = 0; i < activeScene->meshes.size(); i++)
        {
            Object* obj = activeScene->meshes[i];
            obj->uuid = "Mesh_" + std::to_string(i);

            bool isSelected = (activeScene->selectedUUID == obj->uuid);
            if (ImGui::Selectable(obj->uuid.c_str(), isSelected))
                activeScene->selectedUUID = obj->uuid;
        }
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Lights"))
    {
        for (int i = 0; i < activeScene->lights.size(); i++)
        {
            Object* obj = activeScene->lights[i];
            obj->uuid = "Light_" + std::to_string(i);

            bool isSelected = (activeScene->selectedUUID == obj->uuid);
            if (ImGui::Selectable(obj->uuid.c_str(), isSelected))
                activeScene->selectedUUID = obj->uuid;
        }
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Cameras"))
    {
        Object* obj = &activeScene->playerCamera;
        obj->uuid = "Camera_0";

        bool isSelected = (activeScene->selectedUUID == obj->uuid);
        if (ImGui::Selectable(obj->uuid.c_str(), isSelected))
            activeScene->selectedUUID = obj->uuid;

        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Skybox"))
    {
        Object* obj = &activeScene->skyBox;
        obj->uuid = "Skybox_0";

        bool isSelected = (activeScene->selectedUUID == obj->uuid);
        if (ImGui::Selectable(obj->uuid.c_str(), isSelected))
            activeScene->selectedUUID = obj->uuid;

        ImGui::TreePop();
    }

    ImGui::PopStyleVar(2);
    ImGui::End();
}