#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec4 aColor;
layout(location = 3) in vec2 aTexCoord;

out vec4 color;
out vec2 texCoord;
out vec3 currentPos;
out vec3 normal;
out vec4 fragPosLight;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;
uniform mat4 lightProjection;

void main()
{
    vec4 worldPos = modelMat * vec4(aPosition, 1.0);
    gl_Position = projMat * viewMat * worldPos;

    currentPos = worldPos.xyz;
    normal = normalize(mat3(transpose(inverse(modelMat))) * aNormal);
    texCoord = aTexCoord;
    color = aColor;
    fragPosLight = lightProjection * vec4(currentPos, 1.0f);
}
