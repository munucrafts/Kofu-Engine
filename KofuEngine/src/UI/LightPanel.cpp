#include "LightPanel.h"
#include <imgui.h>

void LightPanel::RenderUI(Light* light, ObjectType lightType)
{
    if (ImGui::CollapsingHeader("Light Settings", ImGuiTreeNodeFlags_DefaultOpen))
    {
        float totalAvail = ImGui::GetContentRegionAvail().x;
        float labelWidth = 100.0f;
        float btnSize = ImGui::GetFrameHeight();

        float inputWidth = totalAvail - labelWidth - btnSize;

        ImVec4 labelCol = ImVec4(1.0f, 0.70f, 0.0f, 1.0f);
        ImVec4 textWhite = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 5));

        auto DrawRow = [&](const char* label, const char* btnIcon, const char* id, auto* value, bool isColor = false)
            {
                ImGui::SetCursorPosX(ImGui::GetCursorPosX());

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

                if (isColor)
                {
                    ImGui::ColorEdit4(id, (float*)value, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoLabel);
                }
                else
                {
                    ImGui::DragFloat(id, (float*)value, 0.1f, 0.0f, 100.0f, "%.2f");
                }
            };

        DrawRow("Intensity", "I", "##Intensity", &light->lightDetails.intensity);
        DrawRow("Color", "C", "##Col", &light->lightDetails.color.x, true);

        bool isSpot = (lightType == SPOT_LIGHT);
        ImGui::BeginDisabled(!isSpot);
        DrawRow("Inner Cone", "IC", "##Inner", &light->lightDetails.innerCone);
        DrawRow("Outer Cone", "OC", "##Outer", &light->lightDetails.outerCone);
        ImGui::EndDisabled();

        ImGui::PopStyleVar();
    }
}
