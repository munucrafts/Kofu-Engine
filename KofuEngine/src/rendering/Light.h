#pragma once
#include <glm/ext/vector_float3.hpp>
#include <geometry/mesh.h>
#include "iostream"
#include "vector"

enum LightType
{
    POINT_LIGHT, SPOT_LIGHT, DIRECTIONAL_LIGHT
};

class Light
{
public:
	glm::vec3 location;
    glm::vec4 color;
    glm::mat4 lightProj;
    LightType lightType = DIRECTIONAL_LIGHT;

private:
	Mesh lightMesh;

    std::vector<Vertex> lightVertices =
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
    Light(const glm::vec4& col, const glm::vec3& loc, const LightType& type);
	Light() = default;
	~Light() = default;
	void Init();
	void DrawLightMesh();
};

