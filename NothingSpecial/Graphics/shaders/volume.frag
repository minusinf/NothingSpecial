#version 410 core

//uniform vec2 uWindowSize;
uniform sampler2D uBackFace;
//uniform sampler3D uVolumeTex;

in vec3 exPosition;
in vec3 tfPosition;

out vec4 outColor;

void main(void)
{
    vec3 exitPoint = texture(uBackFace, gl_FragCoord.st).xyz;
    outColor = vec4(exitPoint,1);
}