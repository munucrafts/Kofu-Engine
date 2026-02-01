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

        ImGui::BeginDisabled(true);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 5));

        ImGui::Text("Vertices");
        ImGui::SameLine(labelWidth);
        ImGui::PushStyleColor(ImGuiCol_Text, textWhite);
        ImGui::PushStyleColor(ImGuiCol_Button, labelCol);
        ImGui::Button("V", { btnSize, btnSize });
        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(inputWidth);
        ImGui::DragInt("##V", &vertCount, 0, 0, 0, "%d");

        ImGui::Text("Indices");
        ImGui::SameLine(labelWidth);
        ImGui::PushStyleColor(ImGuiCol_Text, textWhite);
        ImGui::PushStyleColor(ImGuiCol_Button, labelCol);
        ImGui::Button("I", { btnSize, btnSize });
        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(inputWidth);
        ImGui::DragInt("##I", &indCount, 0, 0, 0, "%d");

        ImGui::Text("Triangles");
        ImGui::SameLine(labelWidth);
        ImGui::PushStyleColor(ImGuiCol_Text, textWhite);
        ImGui::PushStyleColor(ImGuiCol_Button, labelCol);
        ImGui::Button("T", { btnSize, btnSize });
        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(inputWidth);
        ImGui::DragInt("##T", &triCount, 0, 0, 0, "%d");

        if (meshType == INSTANCED_STATIC_MESH)
        {
            ImGui::Text("Instances");
            ImGui::SameLine(labelWidth);
            ImGui::PushStyleColor(ImGuiCol_Text, textWhite);
            ImGui::PushStyleColor(ImGuiCol_Button, labelCol);
            ImGui::Button("IC", { btnSize, btnSize });
            ImGui::PopStyleColor(2);
            ImGui::SameLine();
            ImGui::SetNextItemWidth(inputWidth);

            InstancedStaticMesh* ISM = static_cast<InstancedStaticMesh*>(mesh);
            ImGui::DragInt("##IC", &ISM->instanceCount, 0, 0, 0, "%d");
        }

        ImGui::PopStyleVar();
        ImGui::EndDisabled();
    }
}