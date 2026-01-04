in vec3 worldPos;
out vec4 fragColor;

float gridMinPixelsBetweenCells = 2.0;
float gridCellSize = 0.5;

vec4 gridColorThin  = vec4(0.25, 0.25, 0.25, 0.5);
vec4 gridColorThick = vec4(0.75, 0.75, 0.75, 0.5);
vec4 gridColorX     = vec4(0.0, 1.0, 0.0, 0.75);
vec4 gridColorY     = vec4(1.0, 0.0, 0.0, 0.75);
vec4 gridBackgroundColor = vec4(0.05, 0.05, 0.05, 0.25);

float log10(float x) { return log(x) / log(10.0); }
float satf(float x) { return clamp(x, 0.0, 1.0); }
vec2  satv(vec2 x)  { return clamp(x, vec2(0.0), vec2(1.0)); }
float max2(vec2 v)  { return max(v.x, v.y); }

void main()
{
    vec2 dvx = vec2(dFdx(worldPos.x), dFdy(worldPos.x));
    vec2 dvy = vec2(dFdx(worldPos.z), dFdy(worldPos.z));

    vec2 dudv = vec2(length(dvx), length(dvy));
    float l = length(dudv);

    float LOD = max(0.0, log10(l * gridMinPixelsBetweenCells / gridCellSize) + 1.0);

    float GridCellSizeLod0 = gridCellSize * pow(10.0, floor(LOD));
    float GridCellSizeLod1 = GridCellSizeLod0 * 10.0;
    float GridCellSizeLod2 = GridCellSizeLod1 * 10.0;

    dudv = max(dudv * 4.0, vec2(1e-4));

    vec2 m0 = mod(worldPos.xz, GridCellSizeLod0) / dudv;
    float Lod0a = max2(1.0 - abs(satv(m0) * 2.0 - 1.0));

    vec2 m1 = mod(worldPos.xz, GridCellSizeLod1) / dudv;
    float Lod1a = max2(1.0 - abs(satv(m1) * 2.0 - 1.0));

    vec2 m2 = mod(worldPos.xz, GridCellSizeLod2) / dudv;
    float Lod2a = max2(1.0 - abs(satv(m2) * 2.0 - 1.0));

    float LOD_fade = fract(LOD);

    vec4 Color = gridBackgroundColor;

    if (Lod2a > 0.0)
    {
        Color = mix(Color, gridColorThick, Lod2a);
    }
    else if (Lod1a > 0.0)
    {
        vec4 c = mix(gridColorThick, gridColorThin, LOD_fade);
        Color = mix(Color, c, Lod1a);
    }
    else
    {
        Color = mix(Color, gridColorThin, Lod0a * (1.0 - LOD_fade));
    }

    vec2 axisAlpha = 1.0 - satv(abs(worldPos.xz) / dudv);

    Color = mix(Color, gridColorY, axisAlpha.x);
    Color = mix(Color, gridColorX, axisAlpha.y);

    fragColor = Color;
}
