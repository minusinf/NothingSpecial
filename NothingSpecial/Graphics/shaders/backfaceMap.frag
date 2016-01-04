#version 330 core

// Diffuse shader
in vec3 exFragPos;
in vec3 exNormal;
in vec4 exColor;
out vec4 outColor;

void main(void)
{
    vec3 norm = exNormal;
    vec3 lightPos = vec3(20,10,40);
    vec3 lightColor = vec3(1,1,1);
    vec3 ambientColor = vec3(0.5,0.5,0.5);
    vec3 dir = normalize(lightPos-exFragPos);
    
    float diff = max(dot(norm, dir), 0.0);
    vec3 diffuse = diff*lightColor;
    vec3 color = (ambientColor+diffuse)*exColor.rgb;
    outColor = vec4(color, 1);
}