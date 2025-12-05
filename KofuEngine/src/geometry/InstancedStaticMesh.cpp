#include "InstancedStaticMesh.h"
#include <Engine.h>
#include <glm/gtc/type_ptr.hpp>

InstancedStaticMesh::InstancedStaticMesh()
{
	objectType = INSTANCED_STATIC_MESH;
}

InstancedStaticMesh::InstancedStaticMesh(const std::vector<Vertex> verts, const std::vector<GLuint> inds)
{
	objectType = INSTANCED_STATIC_MESH;
	vertices = verts;
	indices = inds;
}

void InstancedStaticMesh::DrawMesh(int shaderID)
{
	vao.Bind();

	unsigned int texUnit = 0;
	for (auto& tex : textures)
	{
		tex.second.Bind(texUnit++);
	}

	glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, instanceCount);
}

void InstancedStaticMesh::InitMesh()
{
	StaticMesh::InitMesh();

	instancedVBO.Init(instanceMatrices);

	vao.LinkAttribs(instancedVBO, 4, 4, GL_FLOAT, sizeof(glm::mat4), (void*)0);
	vao.LinkAttribs(instancedVBO, 5, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(1 * sizeof(glm::vec4)));
	vao.LinkAttribs(instancedVBO, 6, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	vao.LinkAttribs(instancedVBO, 7, 4, GL_FLOAT, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);
	glVertexAttribDivisor(7, 1);
}

void InstancedStaticMesh::ClearMesh()
{
	instancedVBO.Delete();
}
