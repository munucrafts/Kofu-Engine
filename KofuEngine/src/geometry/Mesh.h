#pragma once
#include "components/Components.h"

class Mesh
{
public:
	Mesh() = default;
	virtual ~Mesh() = default;
	virtual void InitMeshManually() = 0;
	virtual void InitMesh() = 0;
	virtual void ClearMesh() = 0;
	virtual void DrawMesh() = 0;

public:
	Transform transform = {};
};