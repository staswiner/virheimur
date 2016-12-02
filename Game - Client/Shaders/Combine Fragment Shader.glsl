#version 400 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D ourShine;
uniform sampler2D ourTexture;
uniform sampler2D ourShadow;


void main()
{    
	vec4 Color = texture(ourTexture, TexCoords);
	vec4 BrightColor = texture(ourShine, TexCoords);
	color = BrightColor * 1 + Color * 0.7; 
}
