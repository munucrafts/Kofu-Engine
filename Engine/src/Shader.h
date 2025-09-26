#pragma once
#include "stb_image.h"
#include "Buffers.h"

struct Texture
{
private:
	GLuint id;
	int width, height, numChannels;
	unsigned char* texData;

public:
	Texture() = default;

	void LoadTexture(const char* path)
	{
		stbi_set_flip_vertically_on_load(true);
		texData = stbi_load(path, &width, &height, &numChannels, STBI_rgb_alpha);
	}

	void Init()
	{
		LoadTexture("./assets/textures/spidey.png");

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

	void Bind()
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}

	void Unind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Delete()
	{
		glDeleteTextures(1, &id);
	}
};

struct Shader
{
private:
	const char* vertShaderSource;
	const char* fragShaderSource;
	GLuint shaderProgram;


public:
	Shader() = default;

	GLuint& CreateShaders(const std::string& vertPath, const std::string& fragPath)
	{
		std::string vertCode = LoadShader(vertPath);
		std::string fragCode = LoadShader(fragPath);

		vertShaderSource = vertCode.c_str();
		fragShaderSource = fragCode.c_str();

		GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertShader, 1, &vertShaderSource, nullptr);
		glCompileShader(vertShader);

		GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &fragShaderSource, nullptr);
		glCompileShader(fragShader);

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertShader);
		glAttachShader(shaderProgram, fragShader);
		glLinkProgram(shaderProgram);
		glUseProgram(shaderProgram);

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);

		return shaderProgram;
	}

private:
	std::string LoadShader(const std::string& shaderPath)
	{
		std::ifstream in(shaderPath, std::ios::binary);

		if (in)
		{
			std::string contents;
			in.seekg(0, std::ios::end);
			contents.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&contents[0], contents.size());
			in.close();
			return contents;
		}
		else return "No Data";
	}
};