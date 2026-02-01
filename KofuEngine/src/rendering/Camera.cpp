#include "rendering/Camera.h"
#include <Engine.h>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera()
{
	objectType = CAMERA;
}

void Camera::ApplyCamMatrix(int shaderID)
{
	Engine& engine = Engine::GetEngine();

	viewMat = glm::mat4(1.0f);
	viewMat = glm::lookAt(location, location + direction.forward, direction.up);

	projMat = glm::mat4(1.0f);
	projMat = glm::perspective(glm::radians(engine.activeScene->playerCamera.FOV), engine.activeScene->GetViewportAspectRatio(), engine.activeScene->playerCamera.nearClip, engine.activeScene->playerCamera.farClip);

	glUniformMatrix4fv(glGetUniformLocation(shaderID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
	glUniform1f(glGetUniformLocation(shaderID, "nearClip"), nearClip);
	glUniform1f(glGetUniformLocation(shaderID, "farClip"), farClip);
	glUniform3fv(glGetUniformLocation(shaderID, "camPos"), 1, glm::value_ptr(location));
}

void Camera::ApplyGizmoCamMatrix(int shaderID)
{
	glm::vec3 gizmoCamPos = -direction.forward * 5.0f;
	glm::mat4 gizmoView = glm::lookAt(gizmoCamPos, glm::vec3(0.0f), direction.up);
	glm::mat4 gizmoProj = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 10.0f);

	glUniformMatrix4fv(glGetUniformLocation(shaderID, "viewMat"), 1, GL_FALSE, glm::value_ptr(gizmoView));
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "projMat"), 1, GL_FALSE, glm::value_ptr(gizmoProj));
}