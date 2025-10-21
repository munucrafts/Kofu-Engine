#version 330 core

out vec4 fragColor;

in vec3 texCoords;

uniform samplerCube skyBox;

void main()
{
	fragColor = texture(skyBox, texCoords);
}