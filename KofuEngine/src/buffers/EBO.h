#pragma once
#include "iostream"
#include "vector"
#include <fstream>
#include <sstream>
#include "components/Components.h"
#include <glad/glad.h>

class EBO
{
private:
	GLuint id;

public:
	EBO() = default;
	void Init(const std::vector<GLuint> indices);
	void Init(const unsigned int* indices, const int size);
	void Bind();
	void Unbind();
	void Delete();
};