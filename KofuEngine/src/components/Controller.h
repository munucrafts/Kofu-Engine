#pragma once
#include <geometry/Object.h>
#include "glm/glm.hpp"
#include "components/components.h"


class Camera;

class Controller
{
public:
	static Controller& GetController();
	void Navigate(Camera& camera);

private:
	Controller() = default;
	~Controller() = default;
	Controller(const Controller& instance) = delete;
	void operator= (const Controller& instance) = delete;
};

