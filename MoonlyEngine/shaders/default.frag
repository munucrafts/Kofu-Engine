#version 330 core

out vec4 fragColor;

in vec4 color;
in vec2 texCoord;
in vec3 currentPos;
in vec3 normal;

uniform sampler2D baseTex;
uniform sampler2D normalTex;
uniform sampler2D occlusionTex;
uniform sampler2D metallicTex;

uniform float nearClip;
uniform float farClip;
uniform int renderMode;

uniform vec3 lightPos;
uniform vec4 lightCol;
uniform vec3 camPos;

uniform int lightType;

float MakeLinearDepth(float depth)
{
    return (2.0f * nearClip * farClip) / (farClip + nearClip - (depth * 2.0f - 1.0f) * (farClip - nearClip));
}

vec4 PointLight()
{
    vec3 lightVec = lightPos - currentPos;
    float dist = length(lightVec);
    float a = 3.0f;
    float b = 0.05f;
    float inten = 10.0f / (a * dist * dist + b * dist + 1.0f);

    float ambient = 0.2f;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightVec);
    float diffuse = max(dot(norm, lightDir), 0.0f);

    float specularStrength = 0.7f;
    vec3 viewDir = normalize(camPos - currentPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 4.0f);
    float specular = specularStrength * spec;

    return (texture(baseTex, texCoord) * (diffuse * inten + ambient + specular)) * lightCol;
}

vec4 DirectionalLight()
{
    float ambient = 0.2f;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(vec3(1.0f, 1.0f, 0.0f));
    float diffuse = max(dot(norm, lightDir), 0.0f);

    float specularStrength = 0.7f;
    vec3 viewDir = normalize(camPos - currentPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 4.0f);
    float specular = specularStrength * spec;

    return (texture(baseTex, texCoord) * (diffuse + ambient + specular)) * lightCol * 1.f;
}

vec4 SpotLight()
{
    float outerCone = 0.9f;
    float innerCone = 0.95f;

    float ambient = 0.2f;

    vec3 norm = normalize(normal);
    vec3 lightVec = lightPos - currentPos;
    vec3 lightDir = normalize(lightVec);
    float diffuse = max(dot(norm, lightDir), 0.0f);

    float specularStrength = 0.7f;
    vec3 viewDir = normalize(camPos - currentPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 4.0f);
    float specular = specularStrength * spec;

    float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDir);
    float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

    return (texture(baseTex, texCoord) * (diffuse * inten + ambient + specular * inten)) * lightCol;
}

void main()
{
    switch (renderMode)
    {
        // Lit mode
        case 0:
        {
            fragColor = lightType == 0 ? PointLight() : lightType == 1 ? SpotLight() : DirectionalLight();
        }
        break;

        // Unlit mode
        case 1:
            fragColor = texture(baseTex, texCoord);
            break;

        // Depth view mode
        case 2:
        {
            float linearDepth = MakeLinearDepth(gl_FragCoord.z);
            fragColor = vec4(vec3(linearDepth / farClip), 1.0f);
        }
        break;

        // Normal mode
        case 3:
            fragColor = vec4(normalize(normal) * 0.5f + 0.5f, 1.0f);
            break;

        // Default fallback
        default:
            fragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);
            break;
    }
}
