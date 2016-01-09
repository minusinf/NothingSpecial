#version 410 core

uniform vec2 uWindowSize;
uniform sampler2D uBackFace;
uniform sampler3D uVolumeTex;

in vec3 exPosition;

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
    
    vec3 color = vec3(0);
    float alpha = 0.0;
    float absorption = 0.02;
    
    for (int i=0; i<=1600; ++i)
    {
        // Front to back composition:
        // http://http.developer.nvidia.com/GPUGems/gpugems_ch39.html
        // Acceleration Techniques for GPU-based Volume Rendering
        float intensity = texture(uVolumeTex, c).x;
        c += dir;
        if (intensity < 0.1)
        {
            continue;
        }

        float radiance = 1.0 - pow(1.0-intensity, stepSize*10);
        color += (1.0-alpha)*radiance*sampleColor;
        alpha += (1.0-alpha)*radiance;

        if (alpha >= 1.0)
        {
            alpha = 1.0;
            break;
        }
        
        if (i * stepSize > len)
        {
            break;
        }
    }
    outColor.xyz = color;
    outColor.w = alpha;
}