#version 400 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D ourTexture;

void main()
{    
	vec4 Color = texture(ourTexture, TexCoords);
	float gamma = 2.2;
    Color.rgb = pow(Color.rgb, vec3(1.0/gamma));
	color = Color;
}
