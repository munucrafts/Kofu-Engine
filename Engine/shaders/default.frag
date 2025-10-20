#version 330 core

out vec4 fragColor;

in vec4 color;
in vec2 texCoord;

uniform sampler2D baseTex;
uniform sampler2D normalTex;
uniform sampler2D occlusionTex;
uniform sampler2D metallicTex;

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
    case 0:
        fragColor = texture(baseTex, texCoord);
        break;

    case 1:
        fragColor = texture(baseTex, texCoord);
        break;

    case 2:
        fragColor = vec4(vec3(MakeLinearDepth(gl_FragCoord.z) / farClip), 1.0);
        break;

    case 3:
        fragColor = texture(normalTex, texCoord);
        break;

    default:
        fragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);
        break;
    }
}