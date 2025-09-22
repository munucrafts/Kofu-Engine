#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "Buffers.h"
#include "Shader.h"
#include <Mesh.h>

class Engine
{
public:
	static Engine& GetEngine();
	void InitEngine();
	void RunEngine();
	void QuitEngine();

private:
	bool engineInitialized = false;
	GLFWwindow* window = nullptr;
	int windowWidth = 1024, windowHeight = 720;
	GLuint activeShaderProgramID;
	Shader shader;
	std::vector<Mesh*> meshes;

private:
	Engine() = default;
	~Engine() = default;
	Engine(const Engine& instance) = delete;
	Engine& operator= (const Engine& instance) = delete;
};

