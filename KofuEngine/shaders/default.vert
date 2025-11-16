#version 330 core
#define MAX_LIGHTS 16

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec4 aColor;
layout(location = 3) in vec2 aTexCoord;

out vec4 color;
out vec2 texCoord;
out vec3 currentPos;
out vec3 normal;

out vec4 fragPosLight[MAX_LIGHTS];
uniform mat4 lightProjection[MAX_LIGHTS];

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main()
{
    vec4 worldPos = modelMat * vec4(aPosition, 1.0);
    currentPos = worldPos.xyz;
    normal = normalize(mat3(transpose(inverse(modelMat))) * aNormal);
    texCoord = aTexCoord;
    color = aColor;

    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        fragPosLight[i] = lightProjection[i] * vec4(currentPos, 1.0f);
    }

    gl_Position = projMat * viewMat * worldPos;
}
