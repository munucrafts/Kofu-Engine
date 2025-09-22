#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform float intensity;
uniform sampler2D tex0;

void main()
{
    FragColor = intensity * texture(tex0, texCoord);
}
