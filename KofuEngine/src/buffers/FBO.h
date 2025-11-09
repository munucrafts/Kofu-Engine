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
	bool hasColor = true;
	bool hasDepth = true;
	int samples = 1;
	GLenum colorInternalFormat = GL_RGBA8;
	GLenum depthInternalFormat = GL_DEPTH24_STENCIL8;
};

class FBO
{
public:
    GLuint id = 0;
    GLuint colorTex = 0;
    GLuint depthRBO = 0;
    FramebufferSpec spec;

public:
    FBO() = default;
	void Init(const FramebufferSpec& specData);
	void Resize(int width, int height);
	void Bind();
	void Unbind();
	void Delete();
};