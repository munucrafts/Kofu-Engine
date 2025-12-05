#pragma once
#include "rendering/Light.h"
#include "glad/glad.h"

Light::Light(const LightDetails details)
{
    lightDetails = details;

    lightVertices =
    {
        { glm::vec3(-0.1f, -0.1f,  0.1f), glm::vec3(0.0f), lightDetails.color, glm::vec2(0.0f) },
        { glm::vec3(0.1f, -0.1f,  0.1f), glm::vec3(0.0f), lightDetails.color, glm::vec2(0.0f) },
        { glm::vec3(0.1f,  0.1f,  0.1f), glm::vec3(0.0f), lightDetails.color, glm::vec2(0.0f) },
        { glm::vec3(-0.1f,  0.1f,  0.1f), glm::vec3(0.0f), lightDetails.color, glm::vec2(0.0f) },
        { glm::vec3(-0.1f, -0.1f, -0.1f), glm::vec3(0.0f), lightDetails.color, glm::vec2(0.0f) },
        { glm::vec3(0.1f, -0.1f, -0.1f), glm::vec3(0.0f), lightDetails.color, glm::vec2(0.0f) },
        { glm::vec3(0.1f,  0.1f, -0.1f), glm::vec3(0.0f), lightDetails.color, glm::vec2(0.0f) },
        { glm::vec3(-0.1f,  0.1f, -0.1f), glm::vec3(0.0f), lightDetails.color, glm::vec2(0.0f) }
    };

    lightIndices =
    {
        0, 1, 2,
        0, 2, 3,
        0, 4, 7,
        0, 7, 3,
        3, 7, 6,
        3, 6, 2,
        2, 6, 5,
        2, 5, 1,
        1, 5, 4,
        1, 4, 0,
        4, 5, 6,
        4, 6, 7
    };
}

void Light::Init()
{
	lightMesh = { lightVertices, lightIndices };
	lightMesh.transform.location = lightDetails.location;
	lightMesh.transform.scale = glm::vec3(5.0f);
	lightMesh.InitMeshManually();

    CalculateLightProjection();
}

void Light::DrawLightMesh(int shaderID)
{
	lightMesh.DrawMesh(shaderID);
}

glm::vec3 Light::GetDirection()
{
    float pitch = glm::radians(lightDetails.rotation.x);
    float yaw = glm::radians(lightDetails.rotation.y);

    glm::vec3 dir;
    dir.x = cos(pitch) * sin(yaw);  
    dir.y = sin(pitch);             
    dir.z = -cos(pitch) * cos(yaw); 

    return glm::normalize(dir);
}

void Light::CalculateLightProjection()
{
    if (lightDetails.lightType == DIRECTIONAL_LIGHT)
    {
        glm::mat4 orthoProjection = glm::ortho(-range, range, -range, range, nearPlane, farPlane);
        glm::mat4 lightView = glm::lookAt(lightDetails.location, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        lightDetails.lightProjs.push_back(orthoProjection * lightView);
    }
    else if (lightDetails.lightType == SPOT_LIGHT)
    {
        glm::mat4 persProjection = glm::perspective(glm::radians(lightDetails.outerCone * 2.0f), 1.0f, nearPlane, farPlane);
        glm::mat4 lightView = glm::lookAt(lightDetails.location, lightDetails.location + GetDirection(), glm::vec3(0, 1, 0));
        lightDetails.lightProjs.push_back(persProjection * lightView);
    }
    else
    {
        glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), 1.0f, nearPlane, farPlane);
        lightDetails.lightProjs.push_back(shadowProj * glm::lookAt(lightDetails.location, lightDetails.location + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
        lightDetails.lightProjs.push_back(shadowProj * glm::lookAt(lightDetails.location, lightDetails.location + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
        lightDetails.lightProjs.push_back(shadowProj * glm::lookAt(lightDetails.location, lightDetails.location + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
        lightDetails.lightProjs.push_back(shadowProj * glm::lookAt(lightDetails.location, lightDetails.location + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
        lightDetails.lightProjs.push_back(shadowProj * glm::lookAt(lightDetails.location, lightDetails.location + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
        lightDetails.lightProjs.push_back(shadowProj * glm::lookAt(lightDetails.location, lightDetails.location + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));
    }
}
