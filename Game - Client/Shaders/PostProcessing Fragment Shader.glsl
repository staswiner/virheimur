#version 400 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D ourTexture;

void main()
{    
	vec4 Color = texture(ourTexture, TexCoords);
	color = Color;
	//color = vec4(0.0,1.0,0.0,1.0);
}
