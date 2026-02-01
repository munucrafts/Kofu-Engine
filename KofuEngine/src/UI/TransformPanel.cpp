#include "TransformPanel.h"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>


void TransformPanel::RenderUI(Transform& transform, bool needLoc, bool needRot, bool needScl)
{
    if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
    {
        float totalAvail = ImGui::GetContentRegionAvail().x;
        float labelWidth = 80.0f;
        float btnSize = ImGui::GetFrameHeight();
        float inputWidth = (totalAvail - labelWidth - (btnSize * 3.0f)) / 3.0f;

        ImVec4 xCol = ImVec4(0.9f, 0.2f, 0.2f, 1.0f);
        ImVec4 yCol = ImVec4(0.3f, 0.8f, 0.3f, 1.0f);
        ImVec4 zCol = ImVec4(0.2f, 0.4f, 0.9f, 1.0f);
        ImVec4 xyzTextCol = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 5));

        ImGui::BeginDisabled(!needLoc);
        ImGui::Text("Location");
        ImGui::SameLine(labelWidth);

        ImGui::PushStyleColor(ImGuiCol_Text, xyzTextCol);
        ImGui::PushStyleColor(ImGuiCol_Button, xCol);
        ImGui::Button("X", { btnSize, btnSize });
        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(inputWidth);
        ImGui::DragFloat("##LX", &transform.location.x, 0.1f);
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Text, xyzTextCol);
        ImGui::PushStyleColor(ImGuiCol_Button, yCol);
        ImGui::Button("Y", { btnSize, btnSize });
        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(inputWidth);
        ImGui::DragFloat("##LY", &transform.location.y, 0.1f);
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Text, xyzTextCol);
        ImGui::PushStyleColor(ImGuiCol_Button, zCol);
        ImGui::Button("Z", { btnSize, btnSize });
        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(inputWidth);
        ImGui::DragFloat("##LZ", &transform.location.z, 0.1f);
        ImGui::EndDisabled();

        ImGui::BeginDisabled(!needRot);
        ImGui::Text("Rotation");
        ImGui::SameLine(labelWidth);

        ImGui::PushStyleColor(ImGuiCol_Text, xyzTextCol);
        ImGui::PushStyleColor(ImGuiCol_Button, xCol);
        ImGui::Button("X##R", { btnSize, btnSize });
        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(inputWidth);
        ImGui::DragFloat("##RX", &transform.rotation.x, 0.1f);
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Text, xyzTextCol);
        ImGui::PushStyleColor(ImGuiCol_Button, yCol);
        ImGui::Button("Y##R", { btnSize, btnSize });
        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(inputWidth);
        ImGui::DragFloat("##RY", &transform.rotation.y, 0.1f);
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Text, xyzTextCol);
        ImGui::PushStyleColor(ImGuiCol_Button, zCol);
        ImGui::Button("Z##R", { btnSize, btnSize });
        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(inputWidth);
        ImGui::DragFloat("##RZ", &transform.rotation.z, 0.1f);
        ImGui::EndDisabled();

        ImGui::BeginDisabled(!needScl);
        ImGui::Text("Scale");
        ImGui::SameLine(labelWidth);

        ImGui::PushStyleColor(ImGuiCol_Text, xyzTextCol);
        ImGui::PushStyleColor(ImGuiCol_Button, xCol);
        ImGui::Button("X##S", { btnSize, btnSize });
        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(inputWidth);
        ImGui::DragFloat("##SX", &transform.scale.x, 0.1f);
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Text, xyzTextCol);
        ImGui::PushStyleColor(ImGuiCol_Button, yCol);
        ImGui::Button("Y##S", { btnSize, btnSize });
        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(inputWidth);
        ImGui::DragFloat("##SY", &transform.scale.y, 0.1f);
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Text, xyzTextCol);
        ImGui::PushStyleColor(ImGuiCol_Button, zCol);
        ImGui::Button("Z##S", { btnSize, btnSize });
        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(inputWidth);
        ImGui::DragFloat("##SZ", &transform.scale.z, 0.1f);
        ImGui::EndDisabled();

        ImGui::PopStyleVar();
    }
}