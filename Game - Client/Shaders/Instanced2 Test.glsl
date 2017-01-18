#version 400 core

out vec4 color;

in GS_OUT{
	float instanceID;
float vertexID;
float Height;
float index;
vec3 Normals;
vec3 FragPos;
vec4 UV;
} gs_out;

void main()
{
	color=vec4(1,0,0,1);
}