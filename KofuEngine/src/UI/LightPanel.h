#pragma once
#include <rendering/Light.h>

class LightPanel
{
public:
	LightPanel() = default;
	~LightPanel() = default;
	void RenderUI(Light* light, ObjectType lightType);
};

