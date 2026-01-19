out vec4 fragColor;

in vec3 texCoords;

uniform samplerCube skyBox;

void main()
{
	fragColor = vec4(vec3(texture(skyBox, texCoords)), 1.0);
}