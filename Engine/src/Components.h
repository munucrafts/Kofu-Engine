#pragma once
#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>

struct Transform
{
public:
	glm::vec3 location;
	glm::vec3 rotation;
	glm::vec3 scale;
};

struct Direction
{
public:
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
};