#version 400 core

in vec2 UVs;

out vec4 color;

uniform sampler2D effectTexture;

void main()
{ 
	vec4 color1 = texture2D(effectTexture, UVs);
	color = vec4(color1);
}
