#version 410 core

// Diffuse shader
in vec3 exFragPos;
in vec4 exColor;
out vec4 outColor;

void main(void)
{

    outColor = exColor;
}