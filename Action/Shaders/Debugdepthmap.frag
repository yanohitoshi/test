#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D dephtMap;

void main()
{
    float dephtValue = texture(dephtMap, TexCoords).r;
    FragColor = vec4(vec3(dephtValue),1.0);
}