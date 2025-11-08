#pragma once
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Skybox
{
public:
	Skybox() = default;
	~Skybox() = default;
	void LoadSkybox();
	void DrawSkybox();

private:
	VAO vao;
	VBO vbo;
	EBO ebo;
	GLuint cubeMapTex;
};

