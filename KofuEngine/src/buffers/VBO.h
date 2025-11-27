#pragma once
#include "iostream"
#include "vector"
#include <fstream>
#include <sstream>
#include "components/Components.h"
#include <glad/glad.h>

class VBO
{
private:
	GLuint id;

public:
	VBO() = default;
	void Init(const std::vector<Vertex>& vertices);
	void Init(const std::vector<glm::mat4>& matrices);
	void Init(const float* vertices, const int size);
	void Bind();
	void Unbind();
	void Delete();
};