#pragma once
#include "UIPanel.h"
#include "imgui.h"

class Scene;
enum RenderMode;

class ViewportPanel : public UIPanel
{
public:
	ViewportPanel() = default;
	~ViewportPanel() = default;
	virtual void RenderUI(Scene* activeScene) override;
	bool IsMouseHoveringOnViewport();

private:
	void RenderRenderModeUI(RenderMode& renderMode);

private:
	bool mouseHovering = false;
};

