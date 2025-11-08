#pragma once
#include "stb_image.h"

struct Shader
{
private:
	const char* vertShaderSource;
	const char* fragShaderSource;

public:
	GLuint shaderProgram;

public:
	Shader() = default;
	Shader(const std::string& vertPath, const std::string& fragPath);
	void Activate();

private:
	std::string LoadShader(const std::string& shaderPath);
};