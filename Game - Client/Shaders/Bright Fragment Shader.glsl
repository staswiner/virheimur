#version 400 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D ourTexture;


void main()
{    
	vec4 Color = texture(ourTexture, TexCoords);
	float Brightness = (Color.x * 0.2126) + (Color.y * 0.7152) + (Color.z * 0.0722);
//	float Brightness = (Color.x + Color.y + Color.z) / 3;
	Brightness = Brightness * Brightness * Brightness;
	color = Color * Brightness * 0.7;
}
