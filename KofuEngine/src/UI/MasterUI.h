#pragma once
#include "OutlinerPanel.h"
#include "ViewportPanel.h"
#include "DetailsPanel.h"
#include "StatsPanel.h"

class Scene;

class MasterUI
{
public:
	static MasterUI& GetMasterUI();
	void InitMasterUI();
	void RenderMasterUI(Scene* activeScene);
	bool IsMouseOnViewport();

private:
	MasterUI() = default;
	~MasterUI() = default;
	MasterUI(const MasterUI& instance) = delete;
	void operator=(const MasterUI& instance) = delete;
	void SetUITheme();

private:
	OutlinerPanel outlinerPanel;
	ViewportPanel viewportPanel;
	DetailsPanel detailsPanel;
	StatsPanel statsPanel;
};