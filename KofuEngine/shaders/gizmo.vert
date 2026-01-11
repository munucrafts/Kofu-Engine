layout(location = 0) in vec3 aPosition;
layout(location = 2) in vec4 aColor;
layout(location = 3) in vec2 aTexCoord;

out vec2 texCoord;
out vec4 color;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main()
{
    vec4 worldPos = modelMat * vec4(aPosition, 1.0);
    gl_Position = projMat * viewMat * worldPos;
    texCoord = aTexCoord;
    color = aColor;
}