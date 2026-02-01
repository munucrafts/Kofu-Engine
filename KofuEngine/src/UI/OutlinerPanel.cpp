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

    float gap = 5.0f;
    bool isSelected = false;
    std::map<std::string, int> indexMap;

    if (ImGui::TreeNodeEx("Meshes", flags))
    {
        for (int i = 0; i < activeScene->meshes.size(); i++)
        {
            Object* obj = activeScene->meshes[i];
            std::string typeName = Util::EnumToString(activeScene->meshes[i]->objectType);
            int typeIndex = indexMap[typeName]++;
            std::string uniqueID = typeName + "_" + std::to_string(typeIndex);
            obj->objectID = uniqueID;

            isSelected = (activeScene->selectedObjectID == obj->objectID);
            if (ImGui::Selectable(uniqueID.c_str(), isSelected))
            {
                activeScene->selectedObjectID = obj->objectID;
            }
        }
        ImGui::TreePop();
    }

    ImGui::Dummy(ImVec2(0.0f, gap));

    if (ImGui::TreeNodeEx("Lights", flags))
    {
        for (int i = 0; i < activeScene->lights.size(); i++)
        {
            Object* obj = activeScene->lights[i];
            std::string typeName = Util::EnumToString(activeScene->lights[i]->lightDetails.lightType);
            int typeIndex = indexMap[typeName]++;
            std::string uniqueID = typeName + "_" + std::to_string(typeIndex);
            obj->objectID = uniqueID;

            isSelected = (activeScene->selectedObjectID == obj->objectID);
            if (ImGui::Selectable(obj->objectID.c_str(), isSelected))
                activeScene->selectedObjectID = obj->objectID;
        }
        ImGui::TreePop();
    }

    ImGui::Dummy(ImVec2(0.0f, gap));

    if (ImGui::TreeNodeEx("Cameras", flags))
    {
        Object* obj = &activeScene->playerCamera;
        obj->objectID = "Camera_0";

        isSelected = (activeScene->selectedObjectID == obj->objectID);
        if (ImGui::Selectable(obj->objectID.c_str(), isSelected))
            activeScene->selectedObjectID = obj->objectID;

        ImGui::TreePop();
    }

    ImGui::Dummy(ImVec2(0.0f, gap));

    if (ImGui::TreeNodeEx("Skybox", flags))
    {
        Object* obj = &activeScene->skyBox;
        obj->objectID = "Skybox_0";

        isSelected = (activeScene->selectedObjectID == obj->objectID);
        if (ImGui::Selectable(obj->objectID.c_str(), isSelected))
            activeScene->selectedObjectID = obj->objectID;

        ImGui::TreePop();
    }

    ImGui::PopStyleVar(2);
    ImGui::End();
}