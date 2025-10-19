#pragma once
#include <vector>
#include <Mesh.h>

struct Scene
{
public:
	void LoadScene();
	void UnloadScene();

public:
	std::vector<Mesh*> meshes;
	std::vector<std::string> modelPaths;
};


