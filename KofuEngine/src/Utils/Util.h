#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <vector>

namespace Util
{
    inline float RandFloat();
    inline float RandFloat(float min, float max);
    inline int RandInt(int min, int max);

    inline glm::vec2 RandVec2(glm::vec2 min, glm::vec2 max);
    inline glm::vec3 RandVec3(glm::vec3 min, glm::vec3 max);
    inline glm::vec4 RandVec4(glm::vec4 min, glm::vec4 max);
   
    void GenerateInstanceMatrices(std::vector<glm::mat4>& instanceMatrices, unsigned int instanceCount, glm::vec3 minBounds, glm::vec3 maxBounds, float minScale, float maxScale
    );
}