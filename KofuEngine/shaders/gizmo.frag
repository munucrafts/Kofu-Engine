out vec4 fragColor;
in vec2 texCoord;
in vec4 color;
uniform sampler2D baseTex;

void main()
{
    //fragColor = texture(baseTex, texCoord);
    fragColor = color;
}