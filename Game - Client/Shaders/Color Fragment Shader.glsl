#version 400 compatibility


uniform vec3 Color;

out vec4 color;


void main()
{ 
	color = vec4( Color,1);
}
