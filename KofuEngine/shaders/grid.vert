layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoords;

out vec2 texCoords;
out vec3 worldPos;

uniform mat4 viewMat;
uniform mat4 projMat;
uniform mat4 modelMat;

void main()
{
	texCoords = aTexCoords; 
	worldPos = vec3(modelMat * vec4(aPosition, 1.0));
	gl_Position = projMat * viewMat * vec4(worldPos, 1.0);
}