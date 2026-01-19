#pragma once
#include <glm/ext/vector_float3.hpp>
#include <geometry/StaticMesh.h>
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

class Light : public Object
{
public:
    LightDetails lightDetails;
    const float range = 25.0f;
    const float nearPlane = 1.0f;
    const float farPlane = 50.0f;

private:
	StaticMesh lightMesh;
    std::vector<Vertex> lightVertices;
    std::vector<GLuint> lightIndices;

public:
    Light(const LightDetails details);
	Light() = default;
	~Light() = default;
	void Init();
	void DrawLightMesh(int shaderID);
    glm::vec3 GetDirection();
    void CalculateLightProjection();
};

