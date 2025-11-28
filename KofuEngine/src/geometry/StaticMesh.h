#pragma once
#include "Mesh.h"
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
#include "map"

class StaticMesh : public Mesh
{
public:
	StaticMesh() = default;
	StaticMesh(const std::vector<Vertex> verts, const std::vector<GLuint> inds);
	~StaticMesh() = default;
	virtual void InitMeshManually() override;
	virtual void InitMesh() override;
	virtual void ClearMesh() override;
	virtual void DrawMesh() override;

public:
	std::map<std::string, Texture> textures;

protected:
	VAO vao;
	VBO vbo;
	EBO ebo;
	glm::mat4 modelMat;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
};