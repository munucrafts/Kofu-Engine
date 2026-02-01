#pragma once
#include "UIPanel.h"
#include <glm/fwd.hpp>
#include <components/Components.h>

class TransformPanel
{
public:
	TransformPanel() = default;
	~TransformPanel() = default;
	void RenderUI(Transform& transform, bool needLoc, bool needRot, bool needScl);
};

