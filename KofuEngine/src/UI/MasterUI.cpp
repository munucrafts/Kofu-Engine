#pragma once
#include "MasterUI.h"
#include "rendering/Scene.h"
#include <Engine.h>
#include "imgui.h"                
#include "backends/imgui_impl_glfw.h"      
#include "backends/imgui_impl_opengl3.h"   

MasterUI& MasterUI::GetMasterUI()
{
	static MasterUI instance;
	return instance;
}

void MasterUI::InitMasterUI()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	Engine& engine = Engine::GetEngine();

	ImGui_ImplGlfw_InitForOpenGL(engine.window, true);
	ImGui_ImplOpenGL3_Init(engine.GetOGLVersionText().c_str());
}

void MasterUI::RenderMasterUI(Scene* activeScene)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    outlinerPanel.RenderUI(activeScene);
    viewportPanel.RenderUI(activeScene);
    detailsPanel.RenderUI(activeScene);

    ImGui::Render();

    ImDrawData* drawData = ImGui::GetDrawData();
    if (drawData) ImGui_ImplOpenGL3_RenderDrawData(drawData);
}
