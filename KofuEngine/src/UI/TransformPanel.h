#pragma once
#include "UIPanel.h"

class TransformPanel : public UIPanel
{
public:
	TransformPanel() = default;
	~TransformPanel() = default;
	virtual void RenderUI() override;
};

