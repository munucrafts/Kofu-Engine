#pragma once
#include "stb_image.h"

struct Shader
{
private:
	GLuint shaderProgram;

public:
	Shader() = default;
	Shader(const std::string& vertPath, const std::string& fragPath, const std::string& geomPath);
    GLuint Activate();
    GLuint GetShaderID();

private:
	bool LoadShader(const std::string& shaderPath, std::string& shaderRef);
};