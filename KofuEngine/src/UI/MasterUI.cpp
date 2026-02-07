#pragma once
#include "MasterUI.h"
#include "rendering/Scene.h"
#include <Engine.h>
#include "imgui.h"                
#include "backends/imgui_impl_glfw.h"      
#include "backends/imgui_impl_opengl3.h"   
#include <imgui_internal.h>

MasterUI& MasterUI::GetMasterUI()
{
	static MasterUI instance;
	return instance;
}

void MasterUI::InitMasterUI()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    SetUITheme();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.Fonts->AddFontFromFileTTF("./assets/fonts/Open_Sans/static/OpenSans-Medium.ttf", 20.0f);

    Engine& engine = Engine::GetEngine();
    ImGui_ImplGlfw_InitForOpenGL(engine.window, true);
    ImGui_ImplOpenGL3_Init(engine.GetOGLVersionText().c_str());
}

bool MasterUI::IsMouseOnViewport()
{
    return viewportPanel.IsMouseHoveringOnViewport();
}

void MasterUI::RenderMasterUI(Scene* activeScene)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGuiID dockspaceID = ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
    static bool layoutInit = false;
    if (!layoutInit)
    {
        layoutInit = true;

        ImGui::DockBuilderRemoveNode(dockspaceID);
        ImGui::DockBuilderAddNode(dockspaceID, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspaceID, ImGui::GetMainViewport()->Size);

        ImGuiID dockCenterID = dockspaceID;

        ImGuiID dockLeftID = ImGui::DockBuilderSplitNode(dockCenterID, ImGuiDir_Left, 0.25f, nullptr, &dockCenterID);
        ImGuiID dockRightID = ImGui::DockBuilderSplitNode(dockCenterID, ImGuiDir_Right, 0.50f, nullptr, &dockCenterID);

        ImGuiID dockLeftBottomID;
        ImGuiID dockLeftTopID = ImGui::DockBuilderSplitNode(dockLeftID, ImGuiDir_Up, 0.5f, nullptr, &dockLeftBottomID);

        ImGuiID dockRightBottomID;
        ImGuiID dockRightTopID = ImGui::DockBuilderSplitNode(dockRightID, ImGuiDir_Up, 0.5f, nullptr, &dockRightBottomID);

        ImGui::DockBuilderDockWindow("Viewport", dockCenterID);
        ImGui::DockBuilderDockWindow("Outliner", dockLeftTopID);
        ImGui::DockBuilderDockWindow("Settings", dockLeftBottomID);
        ImGui::DockBuilderDockWindow("Details", dockRightTopID);
        ImGui::DockBuilderDockWindow("Statistics", dockRightBottomID);

        ImGui::DockBuilderFinish(dockspaceID);
    }

    outlinerPanel.RenderUI(activeScene); 
    viewportPanel.RenderUI(activeScene);
    detailsPanel.RenderUI(activeScene);
    statsPanel.RenderUI(activeScene);
    settingsPanel.RenderUI(activeScene);

    ImGui::Render();

    ImDrawData* drawData = ImGui::GetDrawData();
    if (drawData) ImGui_ImplOpenGL3_RenderDrawData(drawData);

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags& ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(context);
    }
}

void MasterUI::SetUITheme()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // --- MAIN TEXT COLORS ---
    colors[ImGuiCol_Text] = ImVec4(0.10f, 0.12f, 0.15f, 1.00f); // Dark Charcoal
    colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.45f, 0.50f, 1.00f); // Muted Grey-Blue

    // --- WINDOW BACKGROUNDS ---
    colors[ImGuiCol_WindowBg] = ImVec4(0.85f, 0.90f, 0.95f, 1.00f); // Light Frost Blue
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f); // Transparent
    colors[ImGuiCol_PopupBg] = ImVec4(0.90f, 0.93f, 0.97f, 0.98f); // Off-White Blue
    colors[ImGuiCol_Border] = ImVec4(0.70f, 0.75f, 0.82f, 0.50f); // Soft Steel Grey

    // --- TITLE BAR (STEEL BLUE) ---
    colors[ImGuiCol_TitleBg] = ImVec4(0.75f, 0.80f, 0.88f, 1.00f); // Muted Blue
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.60f, 0.70f, 0.95f, 1.00f); // Focused Blue-Grey
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.75f, 0.80f, 0.88f, 0.51f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.80f, 0.85f, 0.92f, 1.00f);

    // --- RECALIBRATED LIME TINTS ---
    ImVec4 limeRest = ImVec4(0.75f, 0.90f, 0.50f, 1.00f); // Lighter, visible green for rest
    ImVec4 limeHover = ImVec4(0.50f, 0.80f, 0.10f, 1.00f); // Darker, saturated green for hover
    ImVec4 limeActive = ImVec4(0.40f, 0.65f, 0.05f, 1.00f); // Deep green for clicking/selected

    // --- TABS & DOCKING ---
    colors[ImGuiCol_Tab] = ImVec4(0.78f, 0.83f, 0.90f, 1.00f); // Background blue-grey
    colors[ImGuiCol_TabHovered] = limeHover;                          // Darker green hover
    colors[ImGuiCol_TabSelected] = limeRest;                           // Light green selected tab
    colors[ImGuiCol_TabSelectedOverline] = limeHover;                          // Bold top line
    colors[ImGuiCol_TabDimmed] = ImVec4(0.82f, 0.87f, 0.92f, 1.00f);
    colors[ImGuiCol_TabDimmedSelected] = ImVec4(0.85f, 0.90f, 0.95f, 1.00f);
    colors[ImGuiCol_TabDimmedSelectedOverline] = ImVec4(0.55f, 0.85f, 0.10f, 0.50f);

    // --- INTERACTIVE FRAMES (INPUTS/SLIDERS) ---
    colors[ImGuiCol_FrameBg] = ImVec4(0.80f, 0.85f, 0.75f, 1.00f); // Very light lime-tinted background
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.70f, 0.80f, 0.60f, 1.00f); // Muted green hover
    colors[ImGuiCol_FrameBgActive] = limeRest;

    // --- BUTTONS (Visible rest state) ---
    colors[ImGuiCol_Button] = limeRest;                           // Now visible at rest
    colors[ImGuiCol_ButtonHovered] = limeHover;                          // Darker on hover
    colors[ImGuiCol_ButtonActive] = limeActive;                         // Darkest on click

    // --- HEADERS (OUTLINER / TREE NODES) ---
    colors[ImGuiCol_Header] = ImVec4(0.75f, 0.90f, 0.50f, 0.60f); // Soft lime rest
    colors[ImGuiCol_HeaderHovered] = limeHover;                          // Darker hover
    colors[ImGuiCol_HeaderActive] = limeActive;                         // Deep green selection

    // --- SCROLLBARS (Polished Lime) ---
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.40f, 0.70f, 0.20f, 0.80f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.70f, 0.20f, 0.90f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.20f, 0.50f, 0.10f, 1.00f);

    // --- WIDGET ACCENTS ---
    colors[ImGuiCol_CheckMark] = limeHover;
    colors[ImGuiCol_SliderGrab] = limeHover;
    colors[ImGuiCol_SliderGrabActive] = limeActive;

    // --- DOCKING & UI BEHAVIOR ---
    colors[ImGuiCol_DockingPreview] = ImVec4(0.55f, 0.85f, 0.10f, 0.40f);
    colors[ImGuiCol_SeparatorHovered] = limeHover;
    colors[ImGuiCol_SeparatorActive] = limeActive;

    // --- STYLE CONFIGURATION ---
    style.WindowRounding = 0.0f;
    style.FrameRounding = 0.0f;
    style.TabRounding = 0.0f;
    style.WindowBorderSize = 0.0f;
    style.FrameBorderSize = 0.0f;
    style.WindowMenuButtonPosition = ImGuiDir_None;
}