#pragma once
#include "UIPanel.h"

class Scene;

class OutlinerPanel : public UIPanel
{
public:
	OutlinerPanel() = default;
	~OutlinerPanel() = default;
	virtual void RenderUI(Scene* activeScene) override;
};

