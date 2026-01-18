#pragma once
#include "UIPanel.h"

class Scene;

class ViewportPanel : public UIPanel
{
public:
	ViewportPanel() = default;
	~ViewportPanel() = default;
	virtual void RenderUI(Scene* activeScene) override;
};

