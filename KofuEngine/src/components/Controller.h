#pragma once
#include <geometry/Object.h>

class Camera;

class Controller
{
public:
	static Controller& GetController();
	static void Navigate(Camera& camera);

private:
	Controller() = default;
	~Controller() = default;
	Controller(const Controller& instance) = delete;
	void operator= (const Controller& instance) = delete;
};

