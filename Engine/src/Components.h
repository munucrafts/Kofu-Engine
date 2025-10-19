#pragma once
#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>

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