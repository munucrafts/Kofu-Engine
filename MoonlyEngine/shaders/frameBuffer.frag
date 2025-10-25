#version 330 core

in vec2 texCoords;
out vec4 fragColor;

uniform sampler2D screenTexture;

void main()
{
	fragColor = vec4(1.0f) - texture(screenTexture, texCoords);
}