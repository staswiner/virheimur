#version 400 core
in vec2 TexCoords;
in vec2 uv;
out vec4 color;

uniform sampler2D ourTexture;
uniform sampler2D ourShadow;
uniform sampler2D ourShine;

const float sampleDist = 1.0;
const float sampleStrength = 2.2; 

vec3 RadialEffect()
{
	float samples[10];
    samples[0] = -0.08;
    samples[1] = -0.05;
    samples[2] = -0.03;
    samples[3] = -0.02;
    samples[4] = -0.01;
    samples[5] =  0.01;
    samples[6] =  0.02;
    samples[7] =  0.03;
    samples[8] =  0.05;
    samples[9] =  0.08;
	
    vec2 dir = 0.5 - uv; 
    float dist = sqrt(dir.x*dir.x + dir.y*dir.y); 
    dir = dir/dist; 
	
    vec4 color = texture(ourTexture,uv); 
    vec4 sum = color;
	
    for (int i = 0; i < 10; i++)
        sum += texture( ourTexture, uv + dir * samples[i] * sampleDist );
	
    sum *= 1.0/11.0;
    float t = dist * sampleStrength;
    t = clamp( t ,0.0,1.0);

   return mix( color, sum, t );
}
void main()
{    
	vec3 texelColor;
	vec2 texelSize = 1.0 / textureSize(ourTexture, 0);
	
	texelColor = RadialEffect();
    color = vec4(texelColor.x, texelColor.y, texelColor.z, 1.0);
}
