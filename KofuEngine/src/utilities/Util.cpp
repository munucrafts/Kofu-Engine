#include "Util.h"


namespace Util
{
    inline float RandFloat()
    {
        return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }

    inline float RandFloat(float min, float max)
    {
        return min + RandFloat() * (max - min);
    }

    inline int RandInt(int min, int max)
    {
        return min + (rand() % (max - min + 1));
    }

    inline glm::vec2 RandVec2(glm::vec2 min, glm::vec2 max)
    {
        return glm::vec2(RandFloat(min.x, max.x), RandFloat(min.y, max.y));
    }

    inline glm::vec3 RandVec3(glm::vec3 min, glm::vec3 max)
    {
        return glm::vec3(RandFloat(min.x, max.x), RandFloat(min.y, max.y), RandFloat(min.z, max.z));
    }

    inline glm::vec4 RandVec4(glm::vec4 min, glm::vec4 max)
    {
        return glm::vec4(RandFloat(min.x, max.x), RandFloat(min.y, max.y), RandFloat(min.z, max.z), RandFloat(min.w, max.w));
    }

    void GenerateInstanceMatrices(std::vector<glm::mat4>& instanceMatrices, unsigned int instanceCount, glm::vec3 minBounds, glm::vec3 maxBounds, float minScale, float maxScale)
    {
        instanceMatrices.clear();
        instanceMatrices.reserve(instanceCount);

        for (unsigned int i = 0; i < instanceCount; i++)
        {
            glm::vec3 position = RandVec3(minBounds, maxBounds);
            glm::quat rotation = glm::quat(glm::vec3(RandFloat(0.0f, glm::two_pi<float>()), RandFloat(0.0f, glm::two_pi<float>()), RandFloat(0.0f, glm::two_pi<float>())));

            float scaleValue = RandFloat(minScale, maxScale);
            glm::vec3 scale(scaleValue);

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, position);
            model *= glm::mat4_cast(rotation);
            model = glm::scale(model, scale);

            instanceMatrices.push_back(model);
        }
    }
}

