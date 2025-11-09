#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "buffers/FBO.h"
#include "rendering/Shader.h"
#include "geometry/mesh.h"
#include <rendering/scene.h>
#include "geometry/Skybox.h"
#include "map"
#include <rendering/Light.h>

class Engine
{
public:
	static Engine& GetEngine();
	void InitEngine();
	void RunEngine();
	void QuitEngine();
	void ClearWindow();
	float GetAspectRatio();

private:
	bool engineInitialized = false;

public:
	GLFWwindow* window = nullptr;
	Scene* activeScene = nullptr;
	int windowWidth = 1280;
	int windowHeight = 1024;

private:
	Engine() = default;
	~Engine() = default;
	Engine(const Engine& instance) = delete;
	Engine& operator= (const Engine& instance) = delete;
};
