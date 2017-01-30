#version 400 core

out vec4 color;

in GS_OUT{
	vec3 VertexID;
} fs_in;

uniform bool indexType;
uniform float Index;

void main()
{
	//color = vec4(fs_in.VertexID.x / 80000.0, fs_in.VertexID.y / 80000.0, fs_in.VertexID.z / 80000.0, 1);ss
	if (indexType == true)
	color = vec4(fs_in.VertexID.x, fs_in.VertexID.y, fs_in.VertexID.z,1);
	if (indexType == false)
	color = vec4(1.0f+Index, 0.0f,0,1.0f);
	//color = vec4(1,0,0,1);
}

