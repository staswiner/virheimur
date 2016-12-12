#version 400 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D ourTexture;
uniform sampler2D ourShadow;
uniform sampler2D ourShine;

const float offset = 1.0/300.0;
vec3 KernelEffect(vec2 texCoords)
{
	vec2 offsets[9] = vec2[](
		vec2(-offset, offset),
		vec2( 0.0f  , offset),
		vec2( offset, offset),
		vec2(-offset, 0.0f),
		vec2( 0.0f  , 0.0f),
		vec2( offset, 0.0f),
		vec2(-offset, -offset),
		vec2( 0.0f  , -offset),
		vec2( offset, -offset)
	);
	
	float kernel[9] = float[](
		-1,+1,+1,
		-1, 1,-1,
		+1,+1,-1
	);
	
	vec3 sampleTex[9];
	for(int i = 0; i < 9; i++)
	{
		sampleTex[i] = vec3(texture(ourTexture, TexCoords.st + offsets[i] + texCoords));
	}
	vec3 col = vec3(0.0);
	for(int i = 0; i < 9; i++)
		col += sampleTex[i] * kernel[i];
	return col;
}
void main()
{    
	vec4 Color = texture(ourTexture, TexCoords);
	//Color = Color * Color * Color * 0.5;
	color = Color;
//	color = vec4(gl_FragCoord.z);
//	vec3 texelColor;
//	vec2 texelSize = 1.0 / textureSize(ourTexture, 0);
//	int Blur = 0;
//	for(int x = -Blur; x <= Blur; x++)
//	{
//		for(int y = -Blur; y <= Blur; y++)
//		{
//			//texelColor += KernelEffect(vec2(x,y) * texelSize);
//			texelColor += vec3(texture(ourTexture, TexCoords + vec2(x,y) * texelSize));
//		}
//	}
//	color = vec4(0.0,1.0,0.0,1.0);
   // color = vec4(texelColor / ((Blur * 2 + 1) * (Blur * 2 + 1 )), 1.0);
}
