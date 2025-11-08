#include "rendering/Camera.h"
#include <Engine.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

void Camera::ApplyCamMatrix()
{
	Engine& engine = Engine::GetEngine();

	viewMat = glm::mat4(1.0f);
	viewMat = glm::lookAt(location, location + direction.forward, direction.up);

	projMat = glm::mat4(1.0f);
	projMat = glm::perspective(glm::radians(engine.FOV), engine.GetAspectRatio(), engine.nearClip, engine.farClip);

	int viewLoc = glGetUniformLocation(engine.activeShaderProgram, "viewMat");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMat));

	int projLoc = glGetUniformLocation(engine.activeShaderProgram, "projMat");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projMat));
}

void Camera::NavigateCamera()
{
	Engine& engine = Engine::GetEngine();
	GLFWwindow* window = engine.window;

	if (!(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS))
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
		return;
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (firstClick)
		{
			glfwSetCursorPos(window, engine.windowWidth / 2, engine.windowHeight / 2);
			firstClick = false;
		}

		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = sensitivity * (float)(mouseY - engine.windowHeight / 2) / engine.windowHeight;
		float rotY = sensitivity * (float)(mouseX - engine.windowWidth / 2) / engine.windowWidth;

		glm::vec3 worldUp(0.0f, 1.0f, 0.0f);
		glm::vec3 newForward = glm::rotate(direction.forward, glm::radians(-rotX), direction.right);

		if (abs(glm::angle(newForward, worldUp) - glm::radians(90.0f)) <= glm::radians(85.0f))
			direction.forward = newForward;

		direction.forward = glm::rotate(direction.forward, glm::radians(-rotY), worldUp);
		direction.forward = glm::normalize(direction.forward);

		direction.right = glm::normalize(glm::cross(direction.forward, worldUp));
		direction.up = glm::normalize(glm::cross(direction.right, direction.forward));

		glfwSetCursorPos(window, engine.windowWidth / 2, engine.windowHeight / 2);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		location += speed * direction.forward;

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		location -= speed * direction.forward;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		location -= speed * glm::normalize(glm::cross(direction.forward, direction.up));

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		location += speed * glm::normalize(glm::cross(direction.forward, direction.up));;

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		location += speed * direction.up;

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		location -= speed * direction.up;
}


