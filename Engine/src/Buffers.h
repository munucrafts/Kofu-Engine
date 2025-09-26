#pragma once
#include "iostream"
#include "vector"
#include <fstream>
#include <sstream>

struct VBO
{
private:
	GLuint id;

public:
	VBO() = default;

	void Init(GLfloat* vertices, size_t size)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
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

	void Init(GLuint* indices, GLsizeiptr size)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
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