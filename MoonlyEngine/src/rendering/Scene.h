#pragma once
#include <vector>
#include <geometry/mesh.h>
#include <rendering/Light.h>

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


