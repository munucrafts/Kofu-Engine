#pragma once
#include "geometry/Skybox.h"
#include "stb_image.h"
#include <Engine.h>
#include <glm/gtc/type_ptr.hpp>


void Skybox::LoadSkybox()
{
	float skyboxVertices[] =
	{
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f
	};

	unsigned int skyboxIndices[] =
	{
		1, 2, 6,
		6, 5, 1,
		0, 4, 7,
		7, 3, 0,
		4, 5, 6,
		6, 7, 4,
		0, 3, 2,
		2, 1, 0,
		0, 1, 5,
		5, 4, 0,
		3, 7, 6,
		6, 2, 3
	};

	std::string cubemapFaceTextures[] =
	{
		"./assets/skybox/right.png",
		"./assets/skybox/left.png",
		"./assets/skybox/top.png",
		"./assets/skybox/bottom.png",
		"./assets/skybox/front.png",
		"./assets/skybox/back.png"
	};

	vao.Init();
	vao.Bind();

	vbo.Init(skyboxVertices, sizeof(skyboxVertices));
	vbo.Bind();

	vao.LinkAttribs(vbo, 0, 3, GL_FLOAT, 0, (void*)0);

	ebo.Init(skyboxIndices, sizeof(skyboxIndices));
	ebo.Bind();

	glGenTextures(1, &cubeMapTex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTex);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	stbi_set_flip_vertically_on_load(false);

	for (int i = 0; i < 6; i++)
	{
		int width, height, numChannels;
		unsigned char* data = stbi_load(cubemapFaceTextures[i].c_str(), &width, &height, &numChannels, 0);
		GLenum format = (numChannels == 4) ? GL_RGBA : GL_RGB;

		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load - " << cubemapFaceTextures[i] << std::endl;
		}
	}
}

void Skybox::DrawSkybox(const GLuint& shaderID)
{
	glUniform1i(glGetUniformLocation(shaderID, "skyBox"), 0);
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_CULL_FACE);

	glm::mat4 viewMat = glm::mat4(1.0f);
	glm::mat4 projectionMat = glm::mat4(1.0f);

	Engine& engine = Engine::GetEngine();

	viewMat = glm::mat4(glm::mat3(glm::lookAt(engine.activeScene->playerCamera.location, engine.activeScene->playerCamera.location + engine.activeScene->playerCamera.direction.forward, engine.activeScene->playerCamera.direction.up)));
	projectionMat = glm::perspective(glm::radians(engine.activeScene->playerCamera.FOV), engine.GetWindowAspectRatio(), engine.activeScene->playerCamera.nearClip, engine.activeScene->playerCamera.farClip);

	glUniformMatrix4fv(glGetUniformLocation(shaderID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "projMat"), 1, GL_FALSE, glm::value_ptr(projectionMat));

	vao.Bind();
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTex);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	vao.Unbind();
}
