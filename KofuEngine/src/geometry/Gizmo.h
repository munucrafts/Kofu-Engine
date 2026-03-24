#pragma once
#include "StaticMesh.h"

class Gizmo
{
public:
	Gizmo() = default;
	~Gizmo() = default;
	void Init();
	void DrawGizmo(GLuint shaderID);

private:
	StaticMesh* gizmoMesh;
};

