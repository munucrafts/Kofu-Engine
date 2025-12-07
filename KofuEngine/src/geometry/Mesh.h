#pragma once
#include "components/Components.h"
#include "rendering/Texture.h"
#include "map"
#include "vector"
#include "iostream"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

struct MeshData
{
	ObjectType meshType;
	Transform transform;
};

class Mesh
{
public:
	Mesh() = default;
	virtual ~Mesh() = default;
	virtual void InitMeshManually() = 0;
	virtual void InitMesh() = 0;
	virtual void ClearMesh() = 0;
	virtual void DrawMesh(int shaderID) = 0;

public:
	Transform transform = {};
	ObjectType objectType = NONE;
	std::map<std::string, Texture> textures;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
};