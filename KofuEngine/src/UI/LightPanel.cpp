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

        ImVec4 labelCol = ImVec4(1.0f, 0.7f, 0.0f, 1.0f);
        ImVec4 textWhite = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 5));

        ImGui::Text("Intensity");
        ImGui::SameLine(labelWidth);
        ImGui::PushStyleColor(ImGuiCol_Text, textWhite);
        ImGui::PushStyleColor(ImGuiCol_Button, labelCol);
        ImGui::Button("I", { btnSize, btnSize });
        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(inputWidth);
        ImGui::DragFloat("##Intensity", &light->lightDetails.intensity, 0.1f, 0.0f, 100.0f, "%.2f");

        ImGui::Text("Color");
        ImGui::SameLine(labelWidth);
        ImGui::PushStyleColor(ImGuiCol_Text, textWhite);
        ImGui::PushStyleColor(ImGuiCol_Button, labelCol);
        ImGui::Button("C", { btnSize, btnSize });
        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(inputWidth);
        ImGui::ColorEdit4("##Col", &light->lightDetails.color.x, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);

        bool isSpot = (lightType == SPOT_LIGHT);
        ImGui::BeginDisabled(!isSpot);

        ImGui::Text("Inner Cone");
        ImGui::SameLine(labelWidth);
        ImGui::PushStyleColor(ImGuiCol_Text, textWhite);
        ImGui::PushStyleColor(ImGuiCol_Button, labelCol);
        ImGui::Button("IC", { btnSize, btnSize });
        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(inputWidth);
        ImGui::DragFloat("##Inner", &light->lightDetails.innerCone, 0.1f, 0.0f, 80.0f, "%.1f");

        ImGui::Text("Outer Cone");
        ImGui::SameLine(labelWidth);
        ImGui::PushStyleColor(ImGuiCol_Text, textWhite);
        ImGui::PushStyleColor(ImGuiCol_Button, labelCol);
        ImGui::Button("OC", { btnSize, btnSize });
        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::SetNextItemWidth(inputWidth);
        ImGui::DragFloat("##Outer", &light->lightDetails.outerCone, 0.1f, 0.0f, 90.0f, "%.1f");

        ImGui::EndDisabled();

        ImGui::PopStyleVar();
    }
}
