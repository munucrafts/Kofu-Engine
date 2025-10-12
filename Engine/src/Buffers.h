#pragma once
#include "iostream"
#include "vector"
#include <fstream>
#include <sstream>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec4 color;
	glm::vec2 texCoord;
};

struct VBO
{
private:
	GLuint id;

public:
	VBO() = default;

	void Init(std::vector<Vertex>& vertices)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	}

	void Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}

	void Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Delete()
	{
		glDeleteBuffers(1, &id);
	}
};

struct VAO
{
private:
	GLuint id;

public:
	VAO() = default;

	void Init()
	{
		glGenVertexArrays(1, &id);
		glBindVertexArray(id);
	}

	void LinkAttribs(VBO& VBO, const GLuint layout, const GLuint numComponents, const GLenum type, const GLsizei stride, void* offset)
	{
		VBO.Bind();
		glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(layout);
		VBO.Unbind();
	}

	void Bind()
	{
		glBindVertexArray(id);
	}

	void Unbind()
	{
		glBindVertexArray(0);
	}

	void Delete()
	{
		glDeleteVertexArrays(1, &id);
	}
};

struct EBO
{
private:
	GLuint id;

public:
	EBO() = default;

	void Init(std::vector<GLuint> indices)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	}

	void Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	void Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void Delete()
	{
		glDeleteBuffers(1, &id);
	}
};