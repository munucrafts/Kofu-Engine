#pragma once
#include "Components.h"

class Camera
{
public:
	Camera() = default;
	~Camera() = default;
	void ApplyCamMatrix();
	void NavigateCamera();

public:
	glm::vec3 location = glm::vec3(0.0f);

	glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);

	float sensitivity = 300.0f;
	float speed = 0.01f;

private:
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	bool firstClick = false;
};

