#pragma once
#include <vector>
#include <Mesh.h>
#include <Light.h>

struct Scene
{
public:
	void LoadScene();
	void UnloadScene();

public:
	std::vector<Mesh*> meshes;
	std::vector<Light*> lights;
	std::vector<std::string> modelPaths;
};


