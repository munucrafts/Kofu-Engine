#pragma once
#include "iostream"
#include "vector"
#include <fstream>
#include <sstream>
#include "Components.h"
#include <glad/glad.h>

class VBO
{
private:
	GLuint id;

public:
	VBO() = default;
	void Init(std::vector<Vertex>& vertices);
	void Init(float* vertices, const int size);
	void Bind();
	void Unbind();
	void Delete();
};