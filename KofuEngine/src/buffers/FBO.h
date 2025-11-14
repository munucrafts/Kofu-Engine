#pragma once
#include "iostream"
#include "vector"
#include <fstream>
#include <sstream>
#include "components/Components.h"
#include <glad/glad.h>
#include "buffers/VAO.h"
#include "buffers/VBO.h"

struct FramebufferSpec
{
	int width = 0;
	int height = 0;
	int samples = 1;
	bool hasColor = true;
	bool hasDepth = true;
	bool depthAsTexture = false;
};

class FBO
{
public:
    GLuint id = 0;
    GLuint colorTex = 0;
    GLuint depthTex = 0;
    GLuint depthRBO = 0;
    FramebufferSpec spec;

public:
    FBO() = default;
	void Init(const FramebufferSpec& specData);
	void Resize(const int width, const int height);
	void Bind();
	void Unbind();
	void Delete();
};