#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "Buffers.h"
#include "Shader.h"

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
	GLuint activeShaderProgramId;
	Shader shader;
	Texture texture;
	VAO vao;
	VBO vbo;
	EBO ebo;

private:
	Engine() = default;
	~Engine() = default;
	Engine(const Engine& instance) = delete;
	Engine& operator= (const Engine& instance) = delete;
};

