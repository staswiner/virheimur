#version 400 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D ourShine;
uniform sampler2D ourTexture;
uniform sampler2D ourShadow;
//uniform sampler2D DepthMap;


void main()
{    
//	vec4 Depth = texture(DepthMap, TexCoords);
	//float near = 50.0f;
	//float far = 100.0f;
	//float depth = Depth.x;
	//float Distance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));
	//Distance = Distance / far;

	vec4 Color = texture(ourTexture, TexCoords);
	vec4 BrightColor = texture(ourShine, TexCoords);
//	color = BrightColor *(Distance) + Color * (1.0 - Distance);
	color = Color * 0.5 + BrightColor * BrightColor * BrightColor * 5.0;
//	color = Color;
}
