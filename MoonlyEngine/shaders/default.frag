#version 330 core

out vec4 fragColor;

in vec4 color;
in vec2 texCoord;
in vec3 currentPos;
in vec3 normal;

uniform sampler2D baseTex;
uniform sampler2D normalTex;
uniform sampler2D occlusionTex;
uniform sampler2D metallicTex;

uniform float nearClip;
uniform float farClip;
uniform int renderMode;

uniform vec3 lightPos;
uniform vec4 lightCol;
uniform vec3 camPos;

float MakeLinearDepth(float depth)
{
    return (2.0f * nearClip * farClip) / (farClip + nearClip - (depth * 2.0f - 1.0f) * (farClip - nearClip));
}

void main()
{
    vec4 baseColor = texture(baseTex, texCoord);

    switch (renderMode)
    {
        // Lit mode
        case 0:
        {
            vec3 norm = normalize(normal);
            vec3 lightDir = normalize(lightPos - currentPos);

            float diffuse = max(dot(norm, lightDir), 0.0f);

            float specularStrength = 0.7f;
            vec3 viewDir = normalize(camPos - currentPos);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 8.0f);
            float specular = specularStrength * spec;

            float ambient = 0.2f;

            vec3 lighting = (ambient + diffuse + specular) * lightCol.rgb;
            fragColor = vec4(baseColor.rgb * lighting, 1.0f);
        }
        break;

        // Unlit mode
        case 1:
            fragColor = baseColor;
            break;

        // Depth view mode
        case 2:
        {
            float linearDepth = MakeLinearDepth(gl_FragCoord.z);
            fragColor = vec4(vec3(linearDepth / farClip), 1.0f);
        }
        break;

        // Normal mode
        case 3:
            fragColor = vec4(normalize(normal) * 0.5f + 0.5f, 1.0f);
            break;

        // Default fallback
        default:
            fragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);
            break;
    }
}
