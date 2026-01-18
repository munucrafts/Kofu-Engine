#pragma once

class Scene;

class UIPanel
{
public:
	UIPanel() = default;
	virtual ~UIPanel() = default;
	virtual void RenderUI(Scene* activeScene) = 0;
};

