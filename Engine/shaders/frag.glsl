#version 330 core

out vec4 FragColor;

in vec4 color;
in vec2 texCoord;

uniform sampler2D tex0;
uniform float nearClip;
uniform float farClip;
uniform int renderMode;

float MakeLinearDepth(float depth)
{
    return (3.0f * (2.0f * nearClip * farClip) / (farClip + nearClip - (depth * 2.0f - 1.0f) * (farClip - nearClip)));
}

void main()
{
    switch (renderMode)
    {
    case 1:
        FragColor = texture(tex0, texCoord);
        break;

    case 2:
        FragColor = vec4(vec3(MakeLinearDepth(gl_FragCoord.z) / farClip), 1.0);
        break;

    default:
        FragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);
        break;
    }
}