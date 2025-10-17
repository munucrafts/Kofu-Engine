#version 330 core

out vec4 FragColor;

in vec4 color;
in vec2 texCoord;

uniform sampler2D tex0;
uniform float nearClip;
uniform float farClip;

float MakeLinearDepth(float depth)
{
    return ((2 * nearClip * farClip) / (farClip + nearClip - (depth * 2 - 1) * (farClip - nearClip)));
}

void main()
{
    FragColor = texture(tex0, texCoord);
    //FragColor = vec4(vec3(MakeLinearDepth(gl_FragCoord.z) / farClip), 1.0f);
}