#version 400

uniform mat4 u_ProjMatrix;
uniform mat4 u_ViewMatrix;

in vec4 in_Position;
in vec4 in_Color;
out vec4 ex_Color;

void main(void)
{
	gl_Position = u_ProjMatrix*u_ViewMatrix*in_Position;
	ex_Color = in_Color;
}
