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
	float GetAspectRatio();

private:
	bool engineInitialized = false;
	Scene activeScene;
	RenderMode renderMode = LIT;
	std::map<std::string, Shader> shaders;

public:
	GLFWwindow* window = nullptr;
	int windowWidth = 1280;
	int windowHeight = 1024;
	GLuint activeShaderProgram = 0;
	float nearClip = 0.1f;
	float farClip = 500.0f;
	Camera playerCamera;
	float FOV = 60.0f;

private:
	Engine() = default;
	~Engine() = default;
	Engine(const Engine& instance) = delete;
	Engine& operator= (const Engine& instance) = delete;
	void ClearWindow();
};
