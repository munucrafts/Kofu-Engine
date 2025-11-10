#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "buffers/VAO.h"
#include "buffers/VBO.h"
#include "buffers/EBO.h"
#include "rendering/Shader.h"
#include "rendering/Texture.h"
#include "components/Components.h"
#include "rendering/Camera.h"

class Mesh
{
public:
	Mesh() = default;
	Mesh(const std::vector<Vertex> verts, const std::vector<GLuint> inds);
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


