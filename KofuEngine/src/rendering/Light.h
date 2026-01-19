#pragma once
#include <glm/ext/vector_float3.hpp>
#include <geometry/StaticMesh.h>
#include "iostream"
#include "vector"

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

