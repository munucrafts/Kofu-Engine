#pragma once
#include "components/Components.h"

class Camera
{
public:
	Camera() = default;
	~Camera() = default;
	void ApplyCamMatrix();
	void NavigateCamera();

public:
	glm::vec3 location = glm::vec3(0.0f);
	Direction direction = { glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) };
	float sensitivity = 300.0f;
	float speed = 0.2f;
	float nearClip = 0.1f;
	float farClip = 500.0f;
	float FOV = 60.0f;

private:
	glm::mat4 viewMat = glm::mat4(1.0f);
	glm::mat4 projMat = glm::mat4(1.0f);
	bool firstClick = false;
};

