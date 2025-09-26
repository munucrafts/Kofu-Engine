#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "Buffers.h"
#include "Shader.h"
#include "Components.h"
#include "Camera.h"

class Mesh
{
public:
	Mesh() = default;
	~Mesh() = default;
	virtual void LoadMesh(const std::string& path);
	virtual void InitMesh();
	virtual void ClearMesh();
	virtual void DrawMesh();

public:
	Transform transform;

private:
	Texture texture;
	VAO vao;
	VBO vbo;
	EBO ebo;
	glm::mat4 model;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
};


