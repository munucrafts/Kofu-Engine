#pragma once
#include <buffers/VAO.h>

class Quad
{
public:
	VAO vao;
	VBO vbo;
	Transform transform;

public:
	void Init(const Transform& worldTransform);
	void Init();
	void DrawQuad(const GLuint& shaderID);
};

