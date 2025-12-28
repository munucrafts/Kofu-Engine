#define MAX_LIGHTS 16

out vec4 fragColor;

in vec4 color;
in vec2 texCoord;
in vec3 currentPos;
in vec3 normal;
in vec4 fragPosLight[MAX_LIGHTS];

uniform sampler2D baseTex;
uniform sampler2D normalTex;
uniform sampler2D occlusionTex;
uniform sampler2D metallicTex;

uniform float nearClip;
uniform float farClip;
uniform float lightFarPlane;

uniform int renderMode;
uniform vec3 camPos;

uniform int lightCount;
uniform int lightTypes[MAX_LIGHTS];
uniform vec3 lightPositions[MAX_LIGHTS];
uniform vec3 lightDirections[MAX_LIGHTS];
uniform vec4 lightColors[MAX_LIGHTS];
uniform float lightIntensities[MAX_LIGHTS];
uniform float lightInnerCones[MAX_LIGHTS];
uniform float lightOuterCones[MAX_LIGHTS];
uniform sampler2D shadowMap[MAX_LIGHTS];
uniform samplerCube shadowCubeMap[MAX_LIGHTS];

float ambient = 0.5;

float MakeLinearDepth(float depth)
{
    return (2.0 * nearClip * farClip) / (farClip + nearClip - (depth * 2.0 - 1.0) * (farClip - nearClip));
}

vec4 PointLight(int lightIndex)
{
    vec3 lightVec = lightPositions[lightIndex] - currentPos;
    float dist = length(lightVec);
    float a = 3.0;
    float b = 0.05;
    float inten = 10.0 / (a * dist * dist + b * dist + 1.0f);

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightVec);
    float diffuse = max(dot(norm, lightDir), 0.0f);

    float specular  = 0.0f;
	if (diffuse > 0.0)
	{
		float specularLight = 0.50f;
		vec3 viewDir = normalize(camPos - currentPos);
		vec3 halfwayVec = normalize(viewDir + lightDir);
		float specAmount = pow(max(dot(normal, halfwayVec), 0.0), 16);
		specular = specAmount * specularLight;
	};

    float shadow = 0.0;
    vec3 lightCoords = fragPosLight[lightIndex].xyz / fragPosLight[lightIndex].w;
    if (lightCoords.z <= 1.0)
    {
        lightCoords = (lightCoords + 1.0) / 2.0;
        float currentDepth = lightCoords.z;
        float bias = max(0.025 * (1.0 - dot(norm, lightDir)), 0.0005);

        int sampleRadius = 2;
        vec2 pixelSize = 1.0 / textureSize(shadowMap[lightIndex], 0);

        for (int y = -sampleRadius; y <= sampleRadius; y++)
        {
            for (int x = -sampleRadius; x <= sampleRadius; x++)
            {
                float closestDepth = texture(shadowMap[lightIndex], lightCoords.xy + vec2(x, y) * pixelSize).r;

                if (currentDepth > closestDepth + bias)
                    shadow += 1.0;
            }
        }

        shadow /= pow((sampleRadius * 2 + 1), 2);
    }

    return lightIntensities[lightIndex] * (texture(baseTex, texCoord) * (diffuse * (1.0f - shadow) + ambient) + specular  * (1.0f - shadow)) * lightColors[lightIndex];
}

vec4 DirectionalLight(int lightIndex)
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPositions[lightIndex]);
    float diffuse = max(dot(norm, lightDir), 0.0);

    float specular = 0.0;
    if (diffuse > 0.0)
    {
        float specularStrength = 0.5;
        vec3 viewDir = normalize(camPos - currentPos);
        vec3 halfway = normalize(viewDir + lightDir);
        specular = pow(max(dot(norm, halfway), 0.0), 16.0) * specularStrength;
    }

    float shadow = 0.0;
    vec3 lightCoords = fragPosLight[lightIndex].xyz / fragPosLight[lightIndex].w;
    if (lightCoords.z <= 1.0)
    {
        lightCoords = (lightCoords + 1.0) / 2.0;
        float currentDepth = lightCoords.z;
        float bias = max(0.025 * (1.0 - dot(norm, lightDir)), 0.0005);

        int sampleRadius = 2;
        vec2 pixelSize = 1.0 / textureSize(shadowMap[lightIndex], 0);

        for (int y = -sampleRadius; y <= sampleRadius; y++)
        {
            for (int x = -sampleRadius; x <= sampleRadius; x++)
            {
                float closestDepth = texture(shadowMap[lightIndex], lightCoords.xy + vec2(x, y) * pixelSize).r;

                if (currentDepth > closestDepth + bias)
                    shadow += 1.0;
            }
        }

        shadow /= pow((sampleRadius * 2 + 1), 2);
    }

    return lightIntensities[lightIndex] * (texture(baseTex, texCoord) * (diffuse * (1.0f - shadow) + ambient) + specular  * (1.0f - shadow)) * lightColors[lightIndex];
}

vec4 SpotLight(int lightIndex)
{
    float outerCone = lightOuterCones[lightIndex];
    float innerCone = lightInnerCones[lightIndex];

    vec3 norm = normalize(normal);
    vec3 lightVecDir = normalize(lightPositions[lightIndex] - currentPos);
    float diffuse = max(dot(norm, lightVecDir), 0.0f);

    float specular  = 0.0f;
	if (diffuse != 0.0f)
	{
		float specularLight = 0.50f;
		vec3 viewDir = normalize(camPos - currentPos);
		vec3 halfwayVec = normalize(viewDir + lightVecDir);
		float specAmount = pow(max(dot(normal, halfwayVec), 0.0f), 16);
		specular = specAmount * specularLight;
	};

    float angle = dot(lightDirections[lightIndex], -lightVecDir);
    float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

    float shadow = 0.0;
    vec3 lightCoords = fragPosLight[lightIndex].xyz / fragPosLight[lightIndex].w;
    if (lightCoords.z <= 1.0)
    {
        lightCoords = (lightCoords + 1.0) / 2.0;
        float currentDepth = lightCoords.z;
        float bias = max(0.025 * (1.0 - dot(norm, lightVecDir)), 0.0005);

        int sampleRadius = 2;
        vec2 pixelSize = 1.0 / textureSize(shadowMap[lightIndex], 0);

        for (int y = -sampleRadius; y <= sampleRadius; y++)
        {
            for (int x = -sampleRadius; x <= sampleRadius; x++)
            {
                float closestDepth = texture(shadowMap[lightIndex], lightCoords.xy + vec2(x, y) * pixelSize).r;
                if (currentDepth > closestDepth + bias)
                    shadow += 1.0;
            }
        }

        shadow /= pow((sampleRadius * 2 + 1), 2);
    }

    return lightIntensities[lightIndex] * (texture(baseTex, texCoord) * (diffuse * inten * (1.0 - shadow) + ambient + specular * inten * (1.0 - shadow))) * lightColors[lightIndex];
}

void main()
{
    switch (renderMode)
    {
        // Lit mode
        case 0:
        {
            vec4 finalCol = vec4(0.0);

            for (int i = 0; i < lightCount; i++)
            {
                finalCol += lightTypes[i] == 0 ? PointLight(i) : lightTypes[i] == 1 ? SpotLight(i) : DirectionalLight(i);
            }

            fragColor = finalCol;
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