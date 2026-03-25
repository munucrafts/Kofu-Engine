#pragma once
#include "stb_image.h"
#include "iostream"
#include <glad/glad.h>

class Shader
{
protected:
	GLuint shaderProgram;

public:
	Shader() = default;
	Shader(const std::string& vertPath, const std::string& fragPath, const std::string& geomPath = {});
    GLuint Activate();
    GLuint GetShaderID();

protected:
	bool LoadShader(const std::string& shaderPath, std::string& shaderRef);
};