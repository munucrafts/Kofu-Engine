#pragma once
#include "iostream"
#include "vector"
#include <fstream>
#include <sstream>
#include "Components.h"

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

struct FBO
{
private:
	GLuint id;

public:
	FBO() = default;

	void Init()
	{
		glGenFramebuffers(1, &id);
		glBindFramebuffer(GL_FRAMEBUFFER, id);
	}

	void Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, id);
	}

	void Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Delete()
	{
		glDeleteFramebuffers(1, &id);
	}
};

struct RBO
{
private:
	GLuint id;

public:
	RBO() = default;

	void Init(int width, int height)
	{
		glGenRenderbuffers(1, &id);
		glBindRenderbuffer(GL_RENDERBUFFER, id);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	}

	void Bind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, id);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, id);
	}

	void Unbind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	void Delete()
	{
		glDeleteRenderbuffers(1, &id);
	}
};