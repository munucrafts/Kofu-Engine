#pragma once
#include <geometry/Object.h>

class Camera;

class Controller
{
public:
	static Controller& GetController();
	void Navigate(Camera& camera);
	glm::vec3 ScreenToWorld(const glm::vec2& screenPosition);
	HitData RayCast(const glm::vec3& beginLocation, const glm::vec3& endLocation);

private:
	Controller() = default;
	~Controller() = default;
	Controller(const Controller& instance) = delete;
	void operator= (const Controller& instance) = delete;
};

