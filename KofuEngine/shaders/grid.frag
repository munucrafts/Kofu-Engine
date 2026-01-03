in vec2 texCoords;
out vec4 fragColor;

void main()
{
    vec2 uv = texCoords * 2000.0; 

    vec2 id = floor(uv);
    vec2 gv = fract(uv) - 0.5;

    vec4 col = vec4(0.1); 

    if (id.y < 5.0) col = vec4(0.0); 

    float lineThickness = 0.01;

    if (abs(gv.x) > 0.5 - lineThickness || abs(gv.y) > 0.5 - lineThickness) 
    {
        col = vec4(1.0);
    }

    fragColor = col;
}
