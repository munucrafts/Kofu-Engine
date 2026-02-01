layout(location = 0) in vec3 aPosition;
layout(location = 3) in vec2 aTexCoord;

out vec2 texCoord;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main()
{
    gl_Position = projMat * viewMat * modelMat * vec4(aPosition, 1.0);;
    texCoord = aTexCoord;
}