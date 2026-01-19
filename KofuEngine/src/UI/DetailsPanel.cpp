#include "DetailsPanel.h"
#include <imgui.h>

void DetailsPanel::RenderUI(Scene* activeScene)
{
	ImGui::Begin("Details");

	ImGui::Text("No Selection");

	ImGui::End();
}
