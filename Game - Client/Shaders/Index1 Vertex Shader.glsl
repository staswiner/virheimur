#version 400 core

layout(location = 0) in vec3 position;
uniform mat4 WVM;


out VS_OUT{
	float VertexID;
} vs_out;


void main()
{
	vec4 objectpos;
	objectpos = vec4(position, 1.0);

	gl_Position = WVM * objectpos;
	vs_out.VertexID = gl_VertexID;
}