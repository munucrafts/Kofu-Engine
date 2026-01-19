#pragma once
#include "UI/UIPanel.h"

class Scene;

class StatsPanel : public UIPanel
{
public:
	StatsPanel() = default;
	~StatsPanel() = default;
	virtual void RenderUI(Scene* activeScene) override;
};

