#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 uvs;
layout(location = 3) in ivec4 bonesID;
layout(location = 4) in vec4 Weights;
layout(location = 5) in mat4 modelInst;

out VS_OUT{
	float instanceID;
float vertexID;
float Height;
vec3 FragPos;
mat4 modelMat;

float Time;
} gs_in;
out mat4 ModelMat;

uniform float time;
uniform bool isAnimated;
uniform mat4 WVM;
uniform mat4 Bones[100];


void main()
{
	gl_Position = WVM * modelInst * vec4(position,1.0);
	gs_in.modelMat = modelInst;
	ModelMat = modelInst;
	gs_in.instanceID = gl_InstanceID;
	gs_in.vertexID = gl_VertexID;
	gs_in.FragPos = position;
	gs_in.Height = 1;// modelInst.y;
}