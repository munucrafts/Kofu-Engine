#include "Engine.h"
#include "Shader.h"

Shader::Shader(const std::string& vertPath, const std::string& fragPath)
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
}

void Shader::Activate()
{
	glUseProgram(shaderProgram);
	Engine::GetEngine().activeShaderProgram = shaderProgram;
}

std::string Shader::LoadShader(const std::string& shaderPath)
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
