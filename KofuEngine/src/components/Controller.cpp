#include "Controller.h"
#include "rendering/Camera.h"
#include <Engine.h>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <audio/AudioListener.h>

Controller& Controller::GetController()
{
	static Controller instance;
	return instance;
}

void Controller::Navigate(Camera& camera)
{
	if (!(&camera)) return;

	Engine& engine = Engine::GetEngine();
	GLFWwindow* window = engine.window;

	if (!(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS))
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		camera.firstClick = true;
		return;
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if (camera.firstClick)
		{
			glfwSetCursorPos(window, engine.windowWidth / 2, engine.windowHeight / 2);
			camera.firstClick = false;
		}

		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = camera.sensitivity * (float)(mouseY - engine.windowHeight / 2) / engine.windowHeight;
		float rotY = camera.sensitivity * (float)(mouseX - engine.windowWidth / 2) / engine.windowWidth;

		glm::vec3 worldUp(0.0f, 1.0f, 0.0f);
		glm::vec3 newForward = glm::rotate(camera.direction.forward, glm::radians(-rotX), camera.direction.right);

		if (abs(glm::angle(newForward, worldUp) - glm::radians(90.0f)) <= glm::radians(87.0f))
			camera.direction.forward = newForward;

		camera.direction.forward = glm::rotate(camera.direction.forward, glm::radians(-rotY), worldUp);
		camera.direction.forward = glm::normalize(camera.direction.forward);

		camera.direction.right = glm::normalize(glm::cross(camera.direction.forward, worldUp));
		camera.direction.up = glm::normalize(glm::cross(camera.direction.right, camera.direction.forward));

		glfwSetCursorPos(window, engine.windowWidth / 2, engine.windowHeight / 2);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.location += camera.speed * camera.direction.forward;

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.location -= camera.speed * camera.direction.forward;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.location -= camera.speed * glm::normalize(glm::cross(camera.direction.forward, camera.direction.up));

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.location += camera.speed * glm::normalize(glm::cross(camera.direction.forward, camera.direction.up));;

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.location += camera.speed * camera.direction.up;

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.location -= camera.speed * camera.direction.up;

	AudioListener::GetListener().SetListenerLocation(camera.location);
	AudioListener::GetListener().SetListenerVelocity(camera.direction.forward * camera.speed);
	AudioListener::GetListener().SetListenerOrientation(camera.direction.forward, camera.direction.up);
}
