#include "Engine.h"
#include "rendering/Shader.h"

Shader::Shader(const std::string& vertPath, const std::string& fragPath, const std::string& geomPath)
{
    std::string vertCode, fragCode, geomCode;
    GLuint vertShader = 0, fragShader = 0, geomShader = 0;

    bool vertLoaded = LoadShader(vertPath, vertCode);
    bool fragLoaded = LoadShader(fragPath, fragCode);
    bool geomLoaded = LoadShader(geomPath, geomCode);

    shaderProgram = glCreateProgram();

    if (vertLoaded)
    {
        vertShader = glCreateShader(GL_VERTEX_SHADER);
        const char* src = vertCode.c_str();
        glShaderSource(vertShader, 1, &src, nullptr);
        glCompileShader(vertShader);
        glAttachShader(shaderProgram, vertShader);
    }

    if (fragLoaded)
    {
        fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char* src = fragCode.c_str();
        glShaderSource(fragShader, 1, &src, nullptr);
        glCompileShader(fragShader);
        glAttachShader(shaderProgram, fragShader);
    }

    if (geomLoaded)
    {
        geomShader = glCreateShader(GL_GEOMETRY_SHADER);
        const char* src = geomCode.c_str();
        glShaderSource(geomShader, 1, &src, nullptr);
        glCompileShader(geomShader);
        glAttachShader(shaderProgram, geomShader);
    }

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    glDeleteShader(geomShader);
}


GLuint Shader::Activate()
{
	glUseProgram(shaderProgram);
    return shaderProgram;
}

GLuint Shader::GetShaderID()
{
    return shaderProgram;
}

bool Shader::LoadShader(const std::string& shaderPath, std::string& shaderRef)
{
	std::ifstream in(shaderPath, std::ios::binary);

	if (in)
	{
		in.seekg(0, std::ios::end);
		shaderRef.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&shaderRef[0], shaderRef.size());
		in.close();
		return true;
	}
	else return false;
}
