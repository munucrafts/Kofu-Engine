#pragma once
#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>
#include <vector>
#include <geometry/Object.h>

enum ObjectType
{
	NONE,
	STATIC_MESH,
	SKELETAL_MESH,
	INSTANCED_STATIC_MESH,
	SKY_BOX,
	SCREEN,
	GRID,
	LIGHT_MESH,
	LIGHT_SHADOW,
	POINT_LIGHT_SHADOW,
	GIZMO
};

struct HitData
{
	bool hit;
	glm::vec3 hitLocation;
	Object hitObject;
	float distance;
};

enum RenderMode
{
	LIT, UNLIT, DEPTH, NORMAL
};

enum LightType
{
	POINT_LIGHT, SPOT_LIGHT, DIRECTIONAL_LIGHT
};

struct LightDetails
{
	LightType lightType = DIRECTIONAL_LIGHT;
	float intensity = 1.0f;
	float innerCone = 10.0f;
	float outerCone = 40.0f;
	glm::vec4 color = glm::vec4(1.0f);
	glm::vec3 location = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);
	std::vector<glm::mat4> lightProjs;
};

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec4 color;
	glm::vec2 texCoord;

	glm::ivec4 jointIDs;
	glm::vec4 jointWeights;
};

struct Transform
{
	glm::vec3 location = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(1.0f);
};

struct Direction
{
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
};

struct MeshData
{
	ObjectType meshType = STATIC_MESH;
	Transform transform;
	unsigned int instanceCount = 1;
};