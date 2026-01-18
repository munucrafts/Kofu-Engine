#pragma once
#include "UIPanel.h"

class Scene;

class DetailsPanel : public UIPanel
{
public:
	DetailsPanel() = default;
	~DetailsPanel() = default;
	virtual void RenderUI(Scene* activeScene) override;
};

