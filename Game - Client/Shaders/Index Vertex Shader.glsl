#version 400 core

layout(location = 0) in vec3 position;
//out VS_OUT{
//	float VertexID;
//} vs_out;
uniform mat4 WVM;

void main()
{
	vec4 objectpos = vec4(position, 1.0);

	gl_Position = WVM * objectpos;

	//vs_out.VertexID = float(gl_VertexID);


}