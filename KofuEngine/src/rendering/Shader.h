#pragma once
#include "stb_image.h"

struct Shader
{
public:
	GLuint shaderProgram;

public:
	Shader() = default;
	Shader(const std::string& vertPath, const std::string& fragPath, const std::string& geomPath);
	void Activate();

private:
	bool LoadShader(const std::string& shaderPath, std::string& shaderRef);
};