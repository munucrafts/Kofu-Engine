#include "Scene.h"
#include <GLTFLoader.h>

void Scene::LoadScene()
{
	for (const std::string& path : modelPaths)
	{
		GLTFLoader::GetGltfLoader().LoadGltfModel(path, this);
	}
}

void Scene::UnloadScene()
{
	for (Mesh* mesh : meshes)
	{
		delete mesh;
	}

	meshes.clear();
}
