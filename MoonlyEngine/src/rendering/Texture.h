#pragma once
#include "stb_image.h"
#include <glad/glad.h>

struct Texture
{
private:
	GLuint id;
	int width, height, numChannels;
	unsigned char* texData;

public:
	Texture() = default;
	Texture(const char* path);
	void LoadTexture(const char* path);
	void Init();
	void Bind(int texNum);
	void Unbind();
	void Delete();
};
