out vec4 fragColor;
in vec2 texCoord;
uniform sampler2D baseTex;

void main()
{
    fragColor = texture(baseTex, texCoord);
}