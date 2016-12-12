#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 uvs;
layout(location = 3) in ivec4 bonesID;
layout(location = 4) in vec4 Weights;
uniform mat4 WVM;


//out VS_OUT{
//	float VertexID;
//} vs_out;


void main()
{
	vec4 objectpos;
	objectpos = vec4(position, 1.0);

	gl_Position = WVM * objectpos;
//	vs_out.VertexID = gl_VertexID;
}