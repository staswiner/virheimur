#version 400 compatibility

in vec2 UVs;

out vec4 color;

uniform sampler2D effectTexture;
void main()
{ 
	vec4 Texture = texture2D(effectTexture, UVs);
	color = vec4(Texture);
}
