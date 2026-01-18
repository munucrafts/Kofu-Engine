#pragma once
#include "rendering/Scene.h"
#include "OutlinerPanel.h"
#include <imgui.h>

void OutlinerPanel::RenderUI(Scene* activeScene)
{
	//std::cout << "Outliner Here" << std::endl;

	ImGui::Begin("Scene Outline");

	////for (Mesh* mesh : activeScene->meshes)
	////{
	////	ImGui::Text("Hello there");
	////}

	ImGui::Text("Hello there");
	ImGui::Text("Hello there");
	ImGui::Text("Hello there");
	ImGui::Text("Hello there");

	ImGui::End();

	
	std::cout << activeScene->meshes.size() << std::endl;
}
