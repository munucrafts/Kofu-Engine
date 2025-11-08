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
	void Init(std::vector<GLuint> indices);
	void Init(unsigned int* indices, const int size);
	void Bind();
	void Unbind();
	void Delete();
};