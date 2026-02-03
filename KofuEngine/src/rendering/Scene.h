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
#include <geometry/Gizmo.h>
#include <UI/MasterUI.h>

class Scene
{
public:
	Scene() = default;
	~Scene() = default;
	void BeginScene();
	void RenderScene(const float deltaTime);
	void EndScene();
	float GetViewportAspectRatio();

private:
	void UploadLightData(const GLuint shaderId);
	void ResizeFBOs(const int viewWidth, const int viewHeight);
	void SortObjectsByType();

private:
	std::map<std::string, MeshData> modelPaths;
	std::map<ObjectType, Shader> shaders; 
	std::vector<Mesh*> meshes;
	std::vector<Light*> lights;
	Gizmo worldGizmo;
	Skybox skyBox;
	Quad gridQuad;
	RenderMode renderMode = LIT;
	std::map<std::string, unsigned int> reservedTexSlots = { {"baseTex", 0}, {"normalTex", 1}, {"occlusionTex", 2}, {"metallicTex", 3} };
	FBO msaaSceneFBO;
	FBO screenTexFBO;
	std::vector<FBO> shadowMapFBOs;
	Object* selectedObject;
	const int shadowMapWidth = 2048;
	const int shadowMapHeight = 2048;
	int viewportWidth = 1024;
	int viewportHeight = 720;

public:
	Camera playerCamera;

private:
	friend class MasterUI;
	friend class OutlinerPanel;
	friend class ViewportPanel;
	friend class DetailsPanel;
	friend class StatsPanel;
	friend class SettingsPanel;
};


