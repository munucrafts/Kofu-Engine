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

    const std::string versionStr = Engine::GetEngine().GetOGLVersionText() + "\n";
    const char* versionPtr = versionStr.c_str();

    if (vertLoaded)
    {
        vertShader = glCreateShader(GL_VERTEX_SHADER);
        const char* src[2] = { versionPtr, vertCode.c_str() };
        glShaderSource(vertShader, 2, src, nullptr);
        glCompileShader(vertShader);
        glAttachShader(shaderProgram, vertShader);
    }
    else
    {
        std::string msg = vertPath.length() == 0 ? "Empty Vertex Shader Path" : vertPath;
        std::cerr << "Failed to Load Vertex Shader - (" + msg + ")" << std::endl;
    }

    if (fragLoaded)
    {
        fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char* src[2] = { versionPtr, fragCode.c_str() };
        glShaderSource(fragShader, 2, src, nullptr);
        glCompileShader(fragShader);
        glAttachShader(shaderProgram, fragShader);
    }
    else
    {
        std::string msg = fragPath.length() == 0 ? "Empty Fragment Shader Path" : fragPath;
        std::cerr << "Failed to Load Fragment Shader - (" + msg + ")" << std::endl;
    }

    if (geomLoaded)
    {
        geomShader = glCreateShader(GL_GEOMETRY_SHADER);
        const char* src[2] = { versionPtr, geomCode.c_str() };
        glShaderSource(geomShader, 2, src, nullptr);
        glCompileShader(geomShader);
        glAttachShader(shaderProgram, geomShader);
    }
    else
    {
        std::string msg = geomPath.length() == 0 ? "Empty Geometry Shader Path" : geomPath;
        std::cerr << "Failed to Load Geometry Shader - (" + msg + ")" << std::endl;
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
    else
    {
        std::cerr << "Shader Path (" + std::string(shaderPath.length() == 0 ? "Empty Path" : shaderPath) + ") is Empty. No Shader Loaded." << std::endl;
        return false;
    }
}
