#pragma once
#include "buffers/VAO.h"
#include "buffers/VBO.h"
#include "buffers/EBO.h"
#include "geometry/Object.h"

class Skybox : public Object
{
public:
	Skybox();
	~Skybox() = default;
	void LoadSkybox();
	void DrawSkybox(const GLuint& shaderID);

private:
	VAO vao;
	VBO vbo;
	EBO ebo;
	GLuint cubeMapTex;
};

