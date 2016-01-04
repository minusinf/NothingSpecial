#version 410 core

uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

in vec3 inPosition;

out vec3 exFragPos;

void main(void)
{    
    vec4 pos = vec4(inPosition, 1.0);
	gl_Position = uProjMatrix*uViewMatrix*uModelMatrix*pos;
    exFragPos = inPosition;
}
