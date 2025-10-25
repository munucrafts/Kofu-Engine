#version 330 core

layout(location = 0) in vec3 aPosition;

out vec3 texCoords;

uniform mat4 viewMat;
uniform mat4 projMat;

void main()
{
	vec4 pos = projMat * viewMat * vec4(aPosition, 1.0f);
	gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);
	texCoords = vec3(aPosition.x, aPosition.y, -aPosition.z);
}