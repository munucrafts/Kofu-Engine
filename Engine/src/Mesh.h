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
	Mesh(std::vector<Vertex> verts, std::vector<GLuint> inds);
	~Mesh() = default;
	virtual void InitMesh();
	virtual void ClearMesh();
	virtual void DrawMesh();

public:
	Transform transform;
	Texture texture;

private:
	VAO vao;
	VBO vbo;
	EBO ebo;
	glm::mat4 modelMat;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
};


