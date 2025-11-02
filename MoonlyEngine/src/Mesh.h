#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "Buffers.h"
#include "Shader.h"
#include "Texture.h"
#include "Components.h"
#include "Camera.h"

class Mesh
{
public:
	Mesh() = default;
	Mesh(std::vector<Vertex> verts, std::vector<GLuint> inds);
	~Mesh() = default;
	void InitMeshManually();
	virtual void InitMesh();
	virtual void ClearMesh();
	virtual void DrawMesh();

public:
	Transform transform;
	Texture baseTex;
	Texture normalTex;
	Texture metallicTex;
	Texture occlusionTex;

private:
	VAO vao;
	VBO vbo;
	EBO ebo;
	glm::mat4 modelMat;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
};


