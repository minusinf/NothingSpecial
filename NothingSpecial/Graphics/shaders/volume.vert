#version 410 core

uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

in vec3 inPosition;
out vec3 exPosition;
out vec4 exColor;

void main(void)
{
    exPosition = vec4(inPosition, 1.0);
    gl_Position = uProjMatrix*uViewMatrix*uModelMatrix*exPosition;
    
    exColor = vec4(1,1,1,1);
}