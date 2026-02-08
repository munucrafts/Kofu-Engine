out vec4 fragColor;

uniform bool isSelected;
uniform vec4 selectColor;
uniform float selectMix;

void main()
{
    fragColor = mix(vec4(0.5, 1.7, 1.0, 1.0), selectColor, selectMix);
}
