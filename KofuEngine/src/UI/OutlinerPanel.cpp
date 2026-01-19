#pragma once
#include "rendering/Scene.h"
#include "OutlinerPanel.h"
#include <imgui.h>
#include "geometry/Object.h"
#include <utilities/Util.h>

void OutlinerPanel::RenderUI(Scene* activeScene)
{
    ImGui::Begin("Outliner");

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1.0f, 1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10.0f, 1.0f));
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed;

    bool isSelected = false;
    std::map<std::string, int> indexMap;

    if (ImGui::TreeNodeEx("Meshes", flags))
    {
        for (int i = 0; i < activeScene->meshes.size(); i++)
        {
            Object* obj = activeScene->meshes[i];
            std::string typeName = Util::EnumToString(activeScene->meshes[i]->meshType);
            int typeIndex = indexMap[typeName]++;
            std::string label = typeName + "_" + std::to_string(typeIndex);
            obj->uuid = label;

            isSelected = (activeScene->selectedUUID == obj->uuid);
            if (ImGui::Selectable(label.c_str(), isSelected))
            {
                activeScene->selectedUUID = obj->uuid;
            }
        }
        ImGui::TreePop();
    }

    if (ImGui::TreeNodeEx("Lights", flags))
    {
        for (int i = 0; i < activeScene->lights.size(); i++)
        {
            Object* obj = activeScene->lights[i];
            std::string typeName = Util::EnumToString(activeScene->lights[i]->lightDetails.lightType);
            int typeIndex = indexMap[typeName]++;
            std::string label = typeName + "_" + std::to_string(typeIndex);
            obj->uuid = label;

            isSelected = (activeScene->selectedUUID == obj->uuid);
            if (ImGui::Selectable(obj->uuid.c_str(), isSelected))
                activeScene->selectedUUID = obj->uuid;
        }
        ImGui::TreePop();
    }

    if (ImGui::TreeNodeEx("Cameras", flags))
    {
        Object* obj = &activeScene->playerCamera;
        obj->uuid = "Camera_0";

        isSelected = (activeScene->selectedUUID == obj->uuid);
        if (ImGui::Selectable(obj->uuid.c_str(), isSelected))
            activeScene->selectedUUID = obj->uuid;

        ImGui::TreePop();
    }

    if (ImGui::TreeNodeEx("Skybox", flags))
    {
        Object* obj = &activeScene->skyBox;
        obj->uuid = "Skybox_0";

        isSelected = (activeScene->selectedUUID == obj->uuid);
        if (ImGui::Selectable(obj->uuid.c_str(), isSelected))
            activeScene->selectedUUID = obj->uuid;

        ImGui::TreePop();
    }

    ImGui::PopStyleVar(2);
    ImGui::End();
}