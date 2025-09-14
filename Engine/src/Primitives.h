#pragma once
#include "iostream"
#include "vector"

struct VBO
{
private:
	GLuint id;

public:
	void Init(GLfloat vertices[])
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
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
	void Init()
	{
		glGenVertexArrays(1, &id);
	}

	void LinkAttribs(VBO& VBO, const GLuint layout, const GLuint numComponents, const GLenum type, const GLsizeiptr stride, void* offset)
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

struct Shader
{
private:
	const char* vertShaderSource;
	const char* fragShaderSource;
	GLuint shaderProgram;


public:
	GLuint& CreateShaders(const std::string& vertPath, const std::string& fagPath)
	{
		LoadShader("ss");

		GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertShader, 1, &vertShaderSource, nullptr);
		glCompileShader(vertShader);

		GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fragShaderSource, nullptr);
		glCompileShader(fragShader);

	    shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertShader);
		glAttachShader(shaderProgram, fragShader);
		glLinkProgram(shaderProgram);

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);

		glUseProgram(shaderProgram);

		return shaderProgram;
	}

private:
	void LoadShader(const std::string& shaderPath)
	{
		// Vertex Shader source code
		vertShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"uniform float size;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(size * aPos.x, size * aPos.y, size * aPos.z, 1.0);\n"
			"}\0";
		//Fragment Shader source code
		fragShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"uniform vec4 color;\n"
			"void main()\n"
			"{\n"
			"   FragColor = color;\n"
			"}\n\0";
	}
};