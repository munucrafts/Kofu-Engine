#pragma once
#include <rendering/Camera.h>

class CameraPanel
{
public:
	CameraPanel() = default;
	~CameraPanel() = default;
	void RenderUI(Camera* cam);
};

