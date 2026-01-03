in vec2 texCoords;
out vec4 fragColor;

void main()
{
	fragColor = vec4(texCoords, 1.0f, 1.0f);
}