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

class SkeletalMesh : public Mesh
{
public:
	SkeletalMesh();
	SkeletalMesh(const std::vector<Vertex> verts, const std::vector<GLuint> inds);
	~SkeletalMesh() = default;
	virtual void InitMesh() override;
	virtual void ClearMesh() override;
	virtual void DrawMesh(int shaderID) override;

protected:
	VAO vao;
	VBO vbo;
	EBO ebo;
	glm::mat4 modelMat;
};

