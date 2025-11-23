#pragma once
#include <glm/ext/vector_float3.hpp>
#include <geometry/mesh.h>
#include "iostream"
#include "vector"

enum LightType
{
    POINT_LIGHT, SPOT_LIGHT, DIRECTIONAL_LIGHT
};

struct LightDetails
{
    LightType lightType = DIRECTIONAL_LIGHT;
    float intensity = 1.0f;
    float innerCone = 10.0f;
    float outerCone = 40.0f;
    glm::vec4 color = glm::vec4(1.0f);
    glm::vec3 location = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    std::vector<glm::mat4> lightProjs;
};

class Light
{
public:
    LightDetails lightDetails;

private:
	Mesh lightMesh;

    std::vector<Vertex> lightVertices =
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

    std::vector<GLuint> lightIndices =
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

public:
    Light(const LightDetails details);
	Light() = default;
	~Light() = default;
	void Init();
	void DrawLightMesh();
    glm::vec3 GetDirection();
    void CalculateLightProjection();
};

