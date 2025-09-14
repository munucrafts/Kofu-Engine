#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "Primitives.h"

class Engine
{
public:
	static Engine& GetEngine();
	void InitEngine();
	void RunEngine();
	void QuitEngine();

private:
	GLFWwindow* window = nullptr;
	int windowWidth = 1024, windowHeight = 720;
	GLuint activeShaderProgram = 0;
	VAO vao;
	VBO vbo;
	Shader shader;

private:
	Engine() = default;
	~Engine() = default;
	Engine(const Engine& instance) = delete;
	Engine& operator= (const Engine& instance) = delete;
};

