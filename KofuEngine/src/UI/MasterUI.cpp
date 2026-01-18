#pragma once
#include "MasterUI.h"
#include "rendering/Scene.h"
#include <imgui.h>

MasterUI& MasterUI::GetMasterUI()
{
	static MasterUI instance;
	return instance;
}

void MasterUI::InitMasterUI()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
}

void MasterUI::RenderMasterUI(Scene* activeScene)
{
	outlinerPanel.RenderUI(activeScene);
	viewportPanel.RenderUI(activeScene);
	detailsPanel.RenderUI(activeScene);
}
