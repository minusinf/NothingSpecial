#version 410 core

uniform vec2 uWindowSize;
uniform sampler2D uBackFace;
uniform sampler3D uVolumeTex;

in vec3 exPosition;
in vec3 tfPosition;

out vec4 outColor;


void main(void)
{
    float stepSize = 0.001;
    vec3 sampleColor = vec3(1,1,1);
    
    vec3 backFace = texture(uBackFace, gl_FragCoord.st/uWindowSize).xyz;
    vec3 frontFace = exPosition;
    vec3 dir = backFace-frontFace;
    
    float len = length(dir);
    dir = normalize(dir)*stepSize;

    vec3 c = frontFace;
    
    vec4 color = vec4(0);
    for (int i=0; i<16000; i++)
    {
        float intensity = texture(uVolumeTex, c).x;
        color.xyz += intensity*sampleColor;
        color.w += intensity;
        
        c += dir;
        if (i * stepSize >= len)
        {
            break;
        }
    }
    outColor = color;
    outColor.w = 1.0;
}