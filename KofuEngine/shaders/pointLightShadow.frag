in vec4 fragPos;

uniform vec3 lightPosition;
uniform float farPlane;

void main()
{
    gl_FragDepth = length(fragPos.xyz - lightPosition) / farPlane;
}