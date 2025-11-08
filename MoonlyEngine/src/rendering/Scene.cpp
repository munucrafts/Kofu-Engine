#include "rendering/scene.h"
#include <geometry/GLTFLoader.h>

void Scene::LoadScene()
{
	for (const std::string& path : modelPaths)
	{
		meshes = GLTFLoader::GetGltfLoader().LoadGltfModel(path);
	}
}

void Scene::UnloadScene()
{
	for (Mesh* mesh : meshes)
	{
		delete mesh;
	}

	lights.clear();
	meshes.clear();
}
