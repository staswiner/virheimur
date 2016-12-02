#version 400 core
in vec2 TexCoords;
out vec4 color;


uniform sampler2D ourTexture;
uniform sampler2D ourShadow;
uniform sampler2D ourShine;

const int Blur = 7;
const float offset = 1.0/300.0;
vec3 KernelEffect()
{
	vec2 texelSize = 1.0 / textureSize(ourTexture, 0);
	const int FullBlur = (2 * Blur) + 1;
	float Kernel[FullBlur] = {0.000489,0.002403,0.009246,0.02784,0.065602,0.120999,0.174697,0.197448
		,0.174697,0.120999,0.065602,0.02784	,0.009246,0.002403,0.000489};
	float NoKernel = 1.0f/FullBlur;
	vec3 sampleTex[FullBlur];
	int y = -Blur;
	for(int i = 0; i < FullBlur; i++)
	{
		sampleTex[i] = vec3(texture(ourTexture, TexCoords + vec2(0,y) * texelSize));
		y++;
	}
	vec3 col = vec3(0.0f);
	for(int i = 0; i < FullBlur; i++)
		col += sampleTex[i] * Kernel[i];
	return col;
}
void main()
{    
	vec3 texelColor;
	vec2 texelSize = 1.0 / textureSize(ourTexture, 0);
	

	//for(int y = -Blur; y <= Blur; y++)
	//{
	//	//texelColor += KernelEffect(vec2(0,y) * texelSize);
	//	texelColor += vec3(texture(ourTexture, TexCoords + vec2(0,y) * texelSize));
	//}
	texelColor = KernelEffect();
    color = vec4(texelColor, 1.0);
}
