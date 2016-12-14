#version 400 core

out vec4 color;

in GS_OUT{
	vec3 VertexID;
} fs_in;

void main()
{
	//color = vec4(fs_in.VertexID.x / 80000.0, fs_in.VertexID.y / 80000.0, fs_in.VertexID.z / 80000.0, 1);
	color = vec4(fs_in.VertexID.x, fs_in.VertexID.y, fs_in.VertexID.z,1);
}

