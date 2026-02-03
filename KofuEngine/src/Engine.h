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
#include "rendering/Light.h"

class Engine
{
public:
	static Engine& GetEngine();
	void InitEngine();
	void RunEngine();
	void QuitEngine();
	void ClearWindow(const unsigned int width, const unsigned height, const glm::vec4& clearColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	float GetWindowAspectRatio();
	std::string GetOGLVersionText();

private:
	bool engineInitialized = false;

public:
	GLFWwindow* window = nullptr;
	std::unique_ptr<Scene> activeScene = nullptr;
	static int windowWidth;
	static int windowHeight;
	static bool enableVsync;

private:
	Engine() = default;
	~Engine() = default;
	Engine(const Engine& instance) = delete;
	Engine& operator= (const Engine& instance) = delete;
	static void WindowResize(GLFWwindow* window, int width, int height);
};
