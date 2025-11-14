#version 330 core

out vec4 fragColor;

in vec4 color;
in vec2 texCoord;
in vec3 currentPos;
in vec3 normal;
in vec4 fragPosLight;

uniform sampler2D baseTex;
uniform sampler2D normalTex;
uniform sampler2D occlusionTex;
uniform sampler2D metallicTex;
uniform sampler2D shadowMap;

uniform float nearClip;
uniform float farClip;
uniform int renderMode;

uniform vec3 lightPos;
uniform vec4 lightCol;
uniform vec3 camPos;
uniform int lightType;

float MakeLinearDepth(float depth)
{
    return (2.0f * nearClip * farClip) / (farClip + nearClip - (depth * 2.0f - 1.0f) * (farClip - nearClip));
}

vec4 PointLight()
{
    vec3 lightVec = lightPos - currentPos;
    float dist = length(lightVec);
    float a = 3.0f;
    float b = 0.05f;
    float inten = 10.0f / (a * dist * dist + b * dist + 1.0f);

    float ambient = 0.2f;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightVec);
    float diffuse = max(dot(norm, lightDir), 0.0f);

    float specular  = 0.0f;
	if (diffuse != 0.0f)
	{
		float specularLight = 0.50f;
		vec3 viewDir = normalize(camPos - currentPos);
		vec3 halfwayVec = normalize(viewDir + lightDir);
		float specAmount = pow(max(dot(normal, halfwayVec), 0.0f), 16);
		specular = specAmount * specularLight;
	};

    return (texture(baseTex, texCoord) * (diffuse * inten + ambient + specular)) * lightCol;
}

vec4 DirectionalLight()
{
    float ambient = 0.2f;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(vec3(1.0, 1.0, 0.0));
    float diffuse = max(dot(norm, lightDir), 0.0);

    float specular = 0.0;
    if (diffuse > 0.0)
    {
        float specularStrength = 0.5;
        vec3 viewDir = normalize(camPos - currentPos);
        vec3 halfway = normalize(viewDir + lightDir);
        specular = pow(max(dot(norm, halfway), 0.0), 16.0) * specularStrength;
    }

    // Shadow calculation
    float shadow = 0.0;
    vec3 lightCoords = fragPosLight.xyz / fragPosLight.w;
    if (lightCoords.z <= 1.0)
    {
        lightCoords = (lightCoords + 1.0) / 2.0;
        float currentDepth = lightCoords.z;
        float bias = max(0.025 * (1.0 - dot(norm, lightDir)), 0.0005);

        int sampleRadius = 2;
        vec2 pixelSize = 1.0 / textureSize(shadowMap, 0);

        for (int y = -sampleRadius; y <= sampleRadius; y++)
            for (int x = -sampleRadius; x <= sampleRadius; x++)
            {
                float closestDepth = texture(shadowMap, lightCoords.xy + vec2(x, y) * pixelSize).r;
                if (currentDepth > closestDepth + bias)
                    shadow += 1.0;
            }

        shadow /= pow((sampleRadius * 2 + 1), 2);
    }

    // Combine
    vec4 texColor = texture(baseTex, texCoord);
    vec3 lighting = vec3(ambient + (1.0 - shadow) * (diffuse + specular));
    return texColor * vec4(lighting, 1.0) * lightCol;
}


vec4 SpotLight()
{
    float outerCone = 0.9f;
    float innerCone = 0.95f;

    float ambient = 0.2f;

    vec3 norm = normalize(normal);
    vec3 lightVec = lightPos - currentPos;
    vec3 lightDir = normalize(lightVec);
    float diffuse = max(dot(norm, lightDir), 0.0f);

    float specular  = 0.0f;
	if (diffuse != 0.0f)
	{
		float specularLight = 0.50f;
		vec3 viewDir = normalize(camPos - currentPos);
		vec3 halfwayVec = normalize(viewDir + lightDir);
		float specAmount = pow(max(dot(normal, halfwayVec), 0.0f), 16);
		specular = specAmount * specularLight;
	};

    float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDir);
    float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

    return (texture(baseTex, texCoord) * (diffuse * inten + ambient + specular * inten)) * lightCol;
}

void main()
{
    switch (renderMode)
    {
        // Lit mode
        case 0:
        {
            fragColor = lightType == 0 ? PointLight() : lightType == 1 ? SpotLight() : DirectionalLight();
        }
        break;

        // Unlit mode
        case 1:
            fragColor = texture(baseTex, texCoord);
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
