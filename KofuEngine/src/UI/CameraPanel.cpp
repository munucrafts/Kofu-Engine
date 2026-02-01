#include "CameraPanel.h"
#include <imgui.h>

void CameraPanel::RenderUI(Camera* cam)
{
    if (ImGui::CollapsingHeader("Camera Settings", ImGuiTreeNodeFlags_DefaultOpen))
    {
        float totalAvail = ImGui::GetContentRegionAvail().x;
        float labelWidth = 100.0f;
        float btnSize = ImGui::GetFrameHeight();
        float inputWidth = totalAvail - labelWidth - btnSize;

        ImVec4 labelCol = ImVec4(0.5f, 0.5f, 1.0f, 1.0f);
        ImVec4 textWhite = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 5));

        ImGui::Text("Sensitivity");
        ImGui::SameLine(labelWidth);
        ImGui::PushStyleColor(ImGuiCol_Text, textWhite);
        ImGui::PushStyleColor(ImGuiCol_Button, labelCol);
        ImGui::Button("S", { btnSize, btnSize });
        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(inputWidth);
        ImGui::DragFloat("##Sens", &cam->sensitivity, 1.0f, 0.0f, 1000.0f, "%.1f");

        ImGui::Text("Speed");
        ImGui::SameLine(labelWidth);
        ImGui::PushStyleColor(ImGuiCol_Text, textWhite);
        ImGui::PushStyleColor(ImGuiCol_Button, labelCol);
        ImGui::Button("V", { btnSize, btnSize });
        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(inputWidth);
        ImGui::DragFloat("##Spd", &cam->speed, 0.05f, 0.0f, 100.0f, "%.2f");

        ImGui::Text("FOV");
        ImGui::SameLine(labelWidth);
        ImGui::PushStyleColor(ImGuiCol_Text, textWhite);
        ImGui::PushStyleColor(ImGuiCol_Button, labelCol);
        ImGui::Button("F", { btnSize, btnSize });
        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(inputWidth);
        ImGui::DragFloat("##Fov", &cam->FOV, 0.5f, 1.0f, 120.0f, "%.1f");

        ImGui::Text("Near Clip");
        ImGui::SameLine(labelWidth);
        ImGui::PushStyleColor(ImGuiCol_Text, textWhite);
        ImGui::PushStyleColor(ImGuiCol_Button, labelCol);
        ImGui::Button("NC", { btnSize, btnSize });
        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(inputWidth);
        ImGui::DragFloat("##Near", &cam->nearClip, 0.01f, 0.001f, 10.0f, "%.3f");

        ImGui::Text("Far Clip");
        ImGui::SameLine(labelWidth);
        ImGui::PushStyleColor(ImGuiCol_Text, textWhite);
        ImGui::PushStyleColor(ImGuiCol_Button, labelCol);
        ImGui::Button("FC", { btnSize, btnSize });
        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(inputWidth);
        ImGui::DragFloat("##Far", &cam->farClip, 10.0f, 10.0f, 100000.0f, "%.0f");

        ImGui::PopStyleVar();
    }
}
