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

        auto cameraRow = [&](const char* label, const char* btnIcon, const char* id, float* val, float speed, float min, float max, const char* fmt)
            {
                ImGui::AlignTextToFramePadding();
                ImGui::Text(label);
                ImGui::SameLine(labelWidth);

                ImGui::PushStyleColor(ImGuiCol_Text, textWhite);
                ImGui::PushStyleColor(ImGuiCol_Button, labelCol);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, labelCol);
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, labelCol);

                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, ImGui::GetStyle().FramePadding.y));
                ImGui::Button(btnIcon, { btnSize, btnSize });
                ImGui::PopStyleVar();

                ImGui::PopStyleColor(4);

                ImGui::SameLine();
                ImGui::SetNextItemWidth(inputWidth);
                ImGui::DragFloat(id, val, speed, min, max, fmt);
            };

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 5));

        cameraRow("Sensitivity", "S", "##Sens", &cam->sensitivity, 1.0f, 0.0f, 1000.0f, "%.1f");
        cameraRow("Speed", "V", "##Spd", &cam->speed, 0.05f, 0.0f, 100.0f, "%.2f");
        cameraRow("FOV", "F", "##Fov", &cam->FOV, 0.5f, 1.0f, 120.0f, "%.1f");
        cameraRow("Near Clip", "NC", "##Near", &cam->nearClip, 0.01f, 0.001f, 10.0f, "%.3f");
        cameraRow("Far Clip", "FC", "##Far", &cam->farClip, 10.0f, 10.0f, 100000.0f, "%.0f");

        ImGui::PopStyleVar();
    }
}