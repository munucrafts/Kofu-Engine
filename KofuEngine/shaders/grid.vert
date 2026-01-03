layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoords;

out vec2 texCoords;

uniform mat4 viewMat;
uniform mat4 projMat;
uniform mat4 modelMat;

void main()
{
	gl_Position = projMat * viewMat * (modelMat * vec4(aPosition, 1.0f));
	texCoords = aTexCoords;
}