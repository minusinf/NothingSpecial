#version 400

uniform mat4 u_ProjMatrix;
uniform mat4 u_ViewMatrix;

in vec3 in_Position;
in vec4 in_Color;
out vec4 ex_Color;

void main(void)
{
    vec4 pos = vec4(in_Position, 1.0);
	gl_Position = u_ProjMatrix*u_ViewMatrix*pos;
	ex_Color = in_Color;
}
