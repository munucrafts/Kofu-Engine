#pragma once
#include "iostream"
#include <vector>
#include "StaticMesh.h"

class InstancedStaticMesh : public StaticMesh
{
public:
	unsigned int instanceCount;
	std::vector<glm::mat4> instanceMatrices;
	VBO instancedVBO;

public:
	InstancedStaticMesh() = default;
	InstancedStaticMesh(const std::vector<Vertex> verts, const std::vector<GLuint> inds);
	~InstancedStaticMesh() = default;
	virtual void DrawMesh() override;
	virtual void InitMesh() override;
	virtual void ClearMesh() override;
};

