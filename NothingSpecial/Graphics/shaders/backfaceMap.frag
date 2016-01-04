#version 410 core

in vec3 exFragPos;

out vec4 outColor;

void main(void)
{
    outColor = vec4(exFragPos, 1);
}