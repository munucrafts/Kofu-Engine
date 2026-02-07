#include "TransformPanel.h"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <functional>


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

        auto axisFunc = [&](const char* buttonText, const char* buttonIcon, float* valuePtr, ImVec4 col, bool last = false)
            {
                ImGui::PushStyleColor(ImGuiCol_Text, xyzTextCol);
                ImGui::PushStyleColor(ImGuiCol_Button, col);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, col );
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, col);

                ImGui::Button(buttonText, { btnSize, btnSize });
                ImGui::PopStyleColor(4);
                ImGui::SameLine();
                ImGui::SetNextItemWidth(inputWidth);
                ImGui::DragFloat(buttonIcon, valuePtr, 0.5f);

                if (!last) ImGui::SameLine();
            };

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 5));

        ImGui::BeginDisabled(!needLoc);
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Location");
        ImGui::SameLine(labelWidth);
        axisFunc("X##L", "##LX", &transform.location.x, xCol);
        axisFunc("Y##L", "##LY", &transform.location.y, yCol);
        axisFunc("Z##L", "##LZ", &transform.location.z, zCol, true);
        ImGui::EndDisabled();

        ImGui::BeginDisabled(!needRot);
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Rotation");
        ImGui::SameLine(labelWidth);
        axisFunc("X##R", "##RX", &transform.rotation.x, xCol);
        axisFunc("Y##R", "##RY", &transform.rotation.y, yCol);
        axisFunc("Z##R", "##RZ", &transform.rotation.z, zCol, true);
        ImGui::EndDisabled();

        ImGui::BeginDisabled(!needScl);
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Scale");
        ImGui::SameLine(labelWidth);
        axisFunc("X##S", "##SX", &transform.scale.x, xCol);
        axisFunc("Y##S", "##SY", &transform.scale.y, yCol);
        axisFunc("Z##S", "##SZ", &transform.scale.z, zCol, true);
        ImGui::EndDisabled();

        ImGui::PopStyleVar();
    }
}