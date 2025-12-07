#include "InstancedStaticMesh.h"
#include <Engine.h>
#include <glm/gtc/type_ptr.hpp>

InstancedStaticMesh::InstancedStaticMesh()
{
	objectType = INSTANCED_STATIC_MESH;
}

InstancedStaticMesh::InstancedStaticMesh(const std::vector<Vertex> verts, const std::vector<GLuint> inds, const unsigned int instCount)
{
	instanceCount = instCount;
	objectType = INSTANCED_STATIC_MESH;
	vertices = verts;
	indices = inds;
}

float randf() {
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

// Generates instance matrices with random position, rotation, and scale
void GenerateInstanceMatrices(
	std::vector<glm::mat4>& instanceMatrices,
	unsigned int instanceCount,
	glm::vec3 minBounds,      // min X, Y, Z
	glm::vec3 maxBounds,      // max X, Y, Z
	float minScale = 0.5f,    // minimum uniform scale
	float maxScale = 1.5f     // maximum uniform scale
) {
	instanceMatrices.clear();
	instanceMatrices.reserve(instanceCount);

	for (unsigned int i = 0; i < instanceCount; i++) {
		// Random position
		glm::vec3 position(
			minBounds.x + randf() * (maxBounds.x - minBounds.x),
			minBounds.y + randf() * (maxBounds.y - minBounds.y),
			minBounds.z + randf() * (maxBounds.z - minBounds.z)
		);

		// Random rotation (normalized quaternion)
		glm::quat rotation = glm::normalize(glm::vec3(0.0f));

		// Random uniform scale
		float scaleValue = minScale + randf() * (maxScale - minScale);
		glm::vec3 scale(scaleValue);

		// Build model matrix
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position);
		model *= glm::mat4_cast(rotation);
		model = glm::scale(model, scale);

		instanceMatrices.push_back(model);
	}
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
	GenerateInstanceMatrices(instanceMatrices, instanceCount, glm::vec3(-10, 0, -10), glm::vec3(10, 20, 10), 10.0f, 10.0f);

	if (instanceMatrices.empty())
	{
		std::cout << "Empty Matrices";
		return;
	}

	StaticMesh::InitMesh();

	vao.Bind();

	instancedVBO.Init(instanceMatrices);
	instancedVBO.Bind();

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
