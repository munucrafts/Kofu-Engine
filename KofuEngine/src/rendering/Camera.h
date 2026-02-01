#pragma once
#include "components/Components.h"
#include "geometry/Object.h"

class Camera : public Object
{
public:
	Camera();
	~Camera() = default;
	void ApplyCamMatrix(int shaderID);
	void ApplyGizmoCamMatrix(int shaderID);

public:
	glm::vec3 location = glm::vec3(0.0f);
	Direction direction = { glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) };
	float sensitivity = 300.0f;
	float speed = 0.75f;
	float nearClip = 0.1f;
	float farClip = 10000.0f;
	float FOV = 45.0f;

private:
	glm::mat4 viewMat = glm::mat4(1.0f);
	glm::mat4 projMat = glm::mat4(1.0f);
	bool firstClick = false;

private:
	friend class Controller;
};

