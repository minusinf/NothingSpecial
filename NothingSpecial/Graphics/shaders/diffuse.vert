#version 330 core

// Diffuse shader
uniform mat4 uProjMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

in vec3 inPosition;
in vec4 inColor;
in vec3 inNormal;

out vec3 exFragPos;
out vec3 exNormal;
out vec4 exColor;

void main(void)
{    
    vec4 pos = vec4(inPosition, 1.0);
	gl_Position = uProjMatrix*uViewMatrix*uModelMatrix*pos;
    exFragPos = vec3(uModelMatrix * pos);
	exColor = inColor;
    exNormal = inNormal;
}
