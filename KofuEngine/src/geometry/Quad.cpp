#include "geometry/Quad.h"
#include <glm/gtc/type_ptr.hpp>

void Quad::Init(const Transform& worldTransform)
{
	transform = worldTransform;

	vao.Init();
	vao.Bind();

	float vertices[] = {
		 // Pos (x, y, z)    // Tex (u, v)
		 1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
		 1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,  0.0f, 1.0f
	};

	vbo.Init(vertices, sizeof(vertices));
	vbo.Bind();

	vao.LinkAttribs(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	vao.LinkAttribs(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}

void Quad::Init()
{
	Init(Transform());
}

void Quad::DrawQuad(const GLuint& shaderID)
{
	vao.Bind();

	glm::mat4 modelMat(1.0f);
	modelMat = glm::translate(modelMat, transform.location);
	modelMat = glm::rotate(modelMat, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	modelMat = glm::rotate(modelMat, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMat = glm::rotate(modelMat, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	modelMat = glm::scale(modelMat, transform.scale);

	glUniformMatrix4fv(glGetUniformLocation(shaderID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));

	glDrawArrays(GL_TRIANGLES, 0, 6);
	vao.Unbind();
}
