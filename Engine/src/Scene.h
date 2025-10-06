#pragma once
#include <vector>
#include <Mesh.h>

struct Scene
{
public:
	void LoadScene(Scene* newScene)
	{
		meshes = newScene->meshes;
	};

	void UnloadScene()
	{
		meshes.clear();
	};

public:
	std::vector<Mesh*> meshes;
};


