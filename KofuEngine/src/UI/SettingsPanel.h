#pragma once
#include "UIPanel.h"

class SettingsPanel : public UIPanel
{
public:
	SettingsPanel() = default;
	~SettingsPanel() = default;
	virtual void RenderUI(Scene* activeScene) override;
};

