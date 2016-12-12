#version 400 core

layout (location = 0) in vec3 position;


uniform mat4 WVM;

void main()
{
	gl_Position = WVM * vec4( position, 1.0 );
}