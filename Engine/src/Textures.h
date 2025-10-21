#pragma once
#include "stb_image.h"
#include "Buffers.h"
#include <glad/glad.h>

struct Texture
{
private:
	GLuint id;
	int width, height, numChannels;
	unsigned char* texData;

public:
	Texture() = default;

	Texture(const char* path)
	{
		LoadTexture(path);
	}

	void LoadTexture(const char* path)
	{
		texData = stbi_load(path, &width, &height, &numChannels, STBI_rgb_alpha);
	}

	void Init()
	{
		glGenTextures(1, &id);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(texData);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Bind(int texNum)
	{
		glActiveTexture(texNum);
		glBindTexture(GL_TEXTURE_2D, id);
	}

	void Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Delete()
	{
		glDeleteTextures(1, &id);
	}
};
