#version 410 core

uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

in vec3 inPosition;
out vec3 exPosition;
out vec3 tfPosition;

void main(void)
{
    exPosition = inPosition;
    gl_Position = uProjMatrix*uViewMatrix*uModelMatrix*vec4(inPosition, 1);
    tfPosition = gl_Position.xyz;
}