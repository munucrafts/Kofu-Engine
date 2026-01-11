#pragma once
#include <vector>
#include <map>
#include <geometry/Mesh.h>
#include <geometry/StaticMesh.h>
#include <geometry/SkeletalMesh.h>
#include <rendering/Light.h>
#include <geometry/Skybox.h>
#include <geometry/Quad.h>
#include "RenderTarget.h"
#include <geometry/InstancedStaticMesh.h>

class Scene
{
public:
	Scene() = default;
	~Scene() = default;
	void BeginScene(unsigned int windowWidth, unsigned int windowHeight);
	void RenderScene(unsigned int windowWidth, unsigned int windowHeight, bool windowResized, float deltaTime);
	void EndScene();

private:
	void UploadLightData(const GLuint shaderId);
	void SortMeshesByType();

private:
	std::map<std::string, MeshData> modelPaths;
	std::map<ObjectType, Shader> shaders; 
	std::vector<Mesh*> meshes;
	std::vector<Light*> lights;
	Skybox skyBox;
	RenderMode renderMode = LIT;
	Quad screenQuad;
	Quad gridQuad;
	FBO msaaSceneFBO;
	FBO ppFBO;
	std::vector<FBO> shadowMapFBOs;
	const int shadowMapWidth = 2048;
	const int shadowMapHeight = 2048;
	std::map<std::string, unsigned int> reservedTexSlots = { {"baseTex", 0}, {"normalTex", 1}, {"occlusionTex", 2}, {"metallicTex", 3} };

public:
	Camera playerCamera;
};


