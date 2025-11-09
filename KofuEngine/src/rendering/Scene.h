#pragma once
#include <vector>
#include <map>
#include <geometry/mesh.h>
#include <rendering/Light.h>
#include <geometry/Skybox.h>
#include <geometry/ScreenQuad.h>
#include "RenderTarget.h"

struct Scene
{
public:
	void BeginScene(unsigned int windowWidth, unsigned int windowHeight);
	void RenderScene(unsigned int windowWidth, unsigned int windowHeight);
	void EndScene();

private:
	void LoadScene();
	void UnloadScene();

private:
	std::vector<std::string> modelPaths;
	std::map<std::string, Shader> shaders; 
	std::vector<Mesh*> meshes;
	std::vector<Light*> lights;
	Skybox skyBox;
	ScreenQuad screenQuad;
	FBO msaaSceneFBO;
	FBO ppFBO;
	RenderMode renderMode = LIT;

public:
	Camera playerCamera;
	GLuint activeShaderProgram = 0;
};


