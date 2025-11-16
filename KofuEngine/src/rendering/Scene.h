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
	Scene() = default;
	~Scene() = default;
	void BeginScene(unsigned int windowWidth, unsigned int windowHeight);
	void RenderScene(unsigned int windowWidth, unsigned int windowHeight, bool windowResized, float deltaTime);
	void EndScene();

private:
	std::vector<std::string> modelPaths;
	std::map<std::string, Shader> shaders; 
	std::vector<Mesh*> meshes;
	std::vector<Light*> lights;
	Skybox skyBox;
	RenderMode renderMode = LIT;
	ScreenQuad screenQuad;
	FBO msaaSceneFBO;
	FBO ppFBO;
	std::vector<FBO> shadowMapFBOs;
	int shadowMapWidth = 2048;
	int shadowMapHeight = 2048;

public:
	Camera playerCamera;
	GLuint activeShaderProgram = 0;
};


