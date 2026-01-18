#pragma once
#include "UIPanel.h"
#include "imgui.h"

class Scene;

class ViewportPanel : public UIPanel
{
public:
	ViewportPanel() = default;
	~ViewportPanel() = default;
	virtual void RenderUI(Scene* activeScene) override;

private:
	ImVec2 viewportSize;
};

