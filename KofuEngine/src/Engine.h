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
	void ClearWindow(unsigned int width, unsigned height);
	float GetAspectRatio();

private:
	bool engineInitialized = false;
	static bool windowResized;

public:
	GLFWwindow* window = nullptr;
	std::unique_ptr<Scene> activeScene = nullptr;
	static int windowWidth;
	static int windowHeight;

private:
	Engine() = default;
	~Engine() = default;
	Engine(const Engine& instance) = delete;
	Engine& operator= (const Engine& instance) = delete;
	static void WindowResize(GLFWwindow* window, int width, int height);
};
