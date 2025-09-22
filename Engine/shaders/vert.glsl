#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec3 color;
out vec2 texCoord;

uniform float scale;

void main()
{
    gl_Position = vec4(aPosition * scale, 1.0f);
    color = aColor;
    texCoord = aTexCoord;
}
