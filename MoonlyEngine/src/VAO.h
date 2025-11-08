#pragma once
#include "iostream"
#include "vector"
#include <fstream>
#include <sstream>
#include "Components.h"
#include <glad/glad.h>
#include "VBO.h"

class VAO
{
public:
	GLuint id;

public:
	VAO() = default;
	void Init();
	void LinkAttribs(VBO& VBO, const GLuint layout, const GLuint numComponents, const GLenum type, const GLsizei stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();
};