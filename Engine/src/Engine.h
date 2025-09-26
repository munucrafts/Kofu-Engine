#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "Buffers.h"
#include "Shader.h"
#include "Mesh.h"

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
	std::vector<Mesh*> meshes;

public:
	GLFWwindow* window = nullptr;
	int windowWidth = 1024;
	int windowHeight = 720;
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
