#pragma once
#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>

enum ObjectType
{
	NONE,
	STATIC_MESH,
	INSTANCED_STATIC_MESH,
	SKY_BOX,
	SCREEN,
	LIGHT_MESH,
	LIGHT_SHADOW,
	POINT_LIGHT_SHADOW
};

enum RenderMode
{
	LIT, UNLIT, DEPTH, NORMAL
};

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec4 color;
	glm::vec2 texCoord;
};

struct Transform
{
	glm::vec3 location;
	glm::vec3 rotation;
	glm::vec3 scale;
};

struct Direction
{
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
};

struct MeshData
{
	ObjectType meshType;
	Transform transform;
	unsigned int instanceCount = 1;
};