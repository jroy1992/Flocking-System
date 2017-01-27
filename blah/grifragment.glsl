#version 420 core

layout(location=0) out vec4 fragColor;

uniform vec4 colour;
in vec3 lightIntensity;

void main()
{
    // .rgb since lightIntegrity is vec3
    fragColor.rgb = lightIntensity;
}
