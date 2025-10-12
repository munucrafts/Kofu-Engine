#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "Buffers.h"
#include "Shader.h"
#include "Mesh.h"
#include <Scene.h>

class Engine
{
public:
	static Engine& GetEngine();
	void InitEngine();
	void RunEngine();
	void QuitEngine();
	float GetAspectRatio();

private:
	bool engineInitialized = false;
	Shader shader;
	Scene activeScene;

public:
	GLFWwindow* window = nullptr;
	int windowWidth = 1920;
	int windowHeight = 1080;
	GLuint activeShaderProgramID = 0;
	float nearClip = 0.1f;
	float farClip = 100.0f;
	Camera playerCamera;
	float FOV = 60.0f;

private:
	Engine() = default;
	~Engine() = default;
	Engine(const Engine& instance) = delete;
	Engine& operator= (const Engine& instance) = delete;
};
