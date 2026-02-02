#include "MeshPanel.h"
#include <imgui.h>
#include <imgui_internal.h>
#include <geometry/InstancedStaticMesh.h>

void MeshPanel::RenderUI(Mesh* mesh, ObjectType meshType)
{
    if (ImGui::CollapsingHeader("Mesh Info", ImGuiTreeNodeFlags_DefaultOpen))
    {
        float totalAvail = ImGui::GetContentRegionAvail().x;
        float labelWidth = 80.0f;
        float btnSize = ImGui::GetFrameHeight();
        float inputWidth = totalAvail - labelWidth - btnSize;

        ImVec4 labelCol = ImVec4(0.4f, 0.7f, 1.0f, 1.0f);
        ImVec4 textWhite = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

        int vertCount = (int)mesh->vertices.size();
        int indCount = (int)mesh->indices.size();
        int triCount = indCount / 3;

        auto meshRow = [&](const char* label, const char* btnIcon, const char* id, int* val)
            {
                ImGui::AlignTextToFramePadding();
                ImGui::Text(label);
                ImGui::SameLine(labelWidth);

                ImGui::PushStyleColor(ImGuiCol_Text, textWhite);
                ImGui::PushStyleColor(ImGuiCol_Button, labelCol);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, labelCol);
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, labelCol);

                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 3));
                ImGui::Button(btnIcon, { btnSize, btnSize });
                ImGui::PopStyleVar();

                ImGui::PopStyleColor(4);

                ImGui::SameLine();
                ImGui::SetNextItemWidth(inputWidth);
                ImGui::DragInt(id, val, 0, 0, 0, "%d");
            };

        ImGui::BeginDisabled(true);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 5));

        meshRow("Vertices", "V", "##V", &vertCount);
        meshRow("Indices", "I", "##I", &indCount);
        meshRow("Triangles", "T", "##T", &triCount);

        if (meshType == INSTANCED_STATIC_MESH)
        {
            InstancedStaticMesh* ISM = static_cast<InstancedStaticMesh*>(mesh);
            meshRow("Instances", "IC", "##IC", &ISM->instanceCount);
        }
        else
        {
            int IC = 1;
            meshRow("Instances", "IC", "##IC", &IC);
        }

        ImGui::PopStyleVar();
        ImGui::EndDisabled();
    }
}