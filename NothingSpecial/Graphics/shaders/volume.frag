#version 410 core


in vec3 exPosition;
in vec4 exColor;

uniform sampler3D uVolumeTex;

out vec4 outColor;

void main(void)
{

    outColor = exColor;
}