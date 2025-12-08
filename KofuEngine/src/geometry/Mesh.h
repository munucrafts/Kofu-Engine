#pragma once
#include "components/Components.h"
#include "rendering/Texture.h"
#include "map"
#include "vector"
#include "iostream"
#include "glad/glad.h"
#include "GLFW/glfw3.h"


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
	ObjectType meshType = NONE;
	Transform transform = {};
	std::map<std::string, Texture> textures;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
};