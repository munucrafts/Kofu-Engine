#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "components/Components.h"

namespace Util
{
    inline float RandFloat();
    inline float RandFloat(float min, float max);
    inline int RandInt(int min, int max);

    inline glm::vec2 RandVec2(glm::vec2 min, glm::vec2 max);
    inline glm::vec3 RandVec3(glm::vec3 min, glm::vec3 max);
    inline glm::vec4 RandVec4(glm::vec4 min, glm::vec4 max);
   
    void GenerateInstanceMatrices(std::vector<glm::mat4>& instanceMatrices, unsigned int instanceCount, glm::vec3 minBounds, glm::vec3 maxBounds, float minScale, float maxScale);

    template <typename T>
    inline const char* EnumToString(T value)
    {
        if constexpr (std::is_same_v<T, ObjectType>)
        {
            switch (value)
            {
            case STATIC_MESH:           return "Static_Mesh";
            case SKELETAL_MESH:         return "Skeletal_Mesh";
            case INSTANCED_STATIC_MESH: return "Instanced_Static_Mesh";
            case SKY_BOX:               return "Skybox";
            case SCREEN:                return "Screen";
            case GRID:                  return "Grid";
            case LIGHT_MESH:            return "Light_Mesh";
            case LIGHT_SHADOW:          return "Light_Shadow";
            case POINT_LIGHT_SHADOW:    return "Point_Light_Shadow";
            case GIZMO:                 return "Gizmo";
            default:                    return "None";
            }
        }

        else if constexpr (std::is_same_v<T, RenderMode>)
        {
            switch (value)
            {
            case LIT:    return "Lit";
            case UNLIT:  return "Unlit";
            case DEPTH:  return "Depth";
            case NORMAL: return "Normal";
            default:     return "None";
            }
        }

        else if constexpr (std::is_same_v<T, LightType>)
        {
            switch (value)
            {
            case POINT_LIGHT:       return "Point_Light";
            case SPOT_LIGHT:        return "Spot_Light";
            case DIRECTIONAL_LIGHT: return "Directional_Light";
            default:                return "None";
            }
        }

        return "Undefined";
    }
}