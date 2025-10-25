#pragma once
#include "iostream"
#include "vector"
#include <fstream>
#include <sstream>
#include "Components.h"
#include <glad/glad.h>


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

	void Init(float* vertices, int size)
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

	void Init(std::vector<GLuint> indices)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	}

	void Init(unsigned int* indices, int size)
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

struct FBO
{
private:
	GLuint id;
	GLuint texture;
	GLuint rbo;

	VAO rectVao;
	VBO rectVbo;
	float rectVertices[24] =
	{
		// Coords    // texCoords
		 1.0f, -1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		-1.0f,  1.0f,  0.0f, 1.0f,

		 1.0f,  1.0f,  1.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f,  0.0f, 1.0f
	};

public:
	FBO() = default;

	void Init(int width, int height)
	{
		rectVao.Init();
		rectVao.Bind();

		rectVbo.Init(rectVertices, sizeof(rectVertices));
		rectVbo.Bind();

		rectVao.LinkAttribs(rectVbo, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*)0);
		rectVao.LinkAttribs(rectVbo, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float)));

		glGenFramebuffers(1, &id);
		glBindFramebuffer(GL_FRAMEBUFFER, id);

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	}

	void DrawFrameBuffer(const GLuint shaderProgram)
	{
		rectVao.Bind();
		glUniform1i(glGetUniformLocation(shaderProgram, "screenTexture"), 0);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glBindTexture(GL_TEXTURE_2D, texture);
		glDrawArrays(GL_TRIANGLES, 0, 6);
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