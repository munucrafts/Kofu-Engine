#include "Light.h"
#include "glad/glad.h"


Light::Light(const glm::vec4& col, const glm::vec3& loc, const LightType& type)
{
	location = loc;
	color = col;
    lightType = type;

    lightVertices =
    {
        { glm::vec3(-0.1f, -0.1f,  0.1f), glm::vec3(0.0f), color, glm::vec2(0.0f) },
        { glm::vec3(0.1f, -0.1f,  0.1f), glm::vec3(0.0f), color, glm::vec2(0.0f) },
        { glm::vec3(0.1f,  0.1f,  0.1f), glm::vec3(0.0f), color, glm::vec2(0.0f) },
        { glm::vec3(-0.1f,  0.1f,  0.1f), glm::vec3(0.0f), color, glm::vec2(0.0f) },
        { glm::vec3(-0.1f, -0.1f, -0.1f), glm::vec3(0.0f), color, glm::vec2(0.0f) },
        { glm::vec3(0.1f, -0.1f, -0.1f), glm::vec3(0.0f), color, glm::vec2(0.0f) },
        { glm::vec3(0.1f,  0.1f, -0.1f), glm::vec3(0.0f), color, glm::vec2(0.0f) },
        { glm::vec3(-0.1f,  0.1f, -0.1f), glm::vec3(0.0f), color, glm::vec2(0.0f) }
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
	lightMesh.transform.location = location;
	lightMesh.transform.scale = glm::vec3(5.0f);
	lightMesh.InitMeshManually();
}

void Light::DrawLightMesh()
{
    if (lightType != DIRECTIONAL_LIGHT)
	    lightMesh.DrawMesh();
}
