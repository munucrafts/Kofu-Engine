#include "ComputeShader.h"
#include <Engine.h>

ComputeShader::ComputeShader(const std::string& shaderPath)
{
	std::string compCode; 
	bool compLoaded = LoadShader(shaderPath, compCode);

	if (compLoaded)
	{
		shaderProgram = glCreateProgram();
		GLuint compShader = glCreateShader(GL_COMPUTE_SHADER);

		const std::string versionStr = Engine::GetEngine().GetOGLVersionText() + "\n";
		const char* versionPtr = versionStr.c_str();
		const char* src[2] = {versionPtr, compCode.c_str()};

		glShaderSource(shaderProgram, 2, src, nullptr);
		glCompileShader(shaderProgram);
		glAttachShader(shaderProgram, compShader);
		glLinkProgram(shaderProgram);
		glUseProgram(shaderProgram);
		glDeleteProgram(shaderProgram);

		return;
	}

	std::string msg = shaderPath.length() == 0 ? "Empty Compute Shader Path" : shaderPath;
	std::cerr << "Failed to Load Compute Shader - ( " + msg + " )" << std::endl;
}
