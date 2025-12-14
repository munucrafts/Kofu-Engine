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
	void ClearWindow(const unsigned int width, const unsigned height, const glm::vec4& clearColor = glm::vec4(0.0f));
	float GetAspectRatio();

private:
	static constexpr char engineName[12] = "Kofu Engine";
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
