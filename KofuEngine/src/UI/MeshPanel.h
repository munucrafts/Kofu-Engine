#pragma once
#include <geometry/Mesh.h>

class MeshPanel
{
public:
	MeshPanel() = default;
	~MeshPanel() = default;
	void RenderUI(Mesh* mesh, ObjectType meshType);
};

