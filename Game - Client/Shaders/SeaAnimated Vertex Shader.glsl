#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 uvs;
layout(location = 3) in ivec4 bonesID;
layout(location = 4) in vec4 Weights;
//layout(location = 5) in vec4 modelInst1;
//layout(location = 6) in vec4 modelInst2;
//layout(location = 7) in vec4 modelInst3;
//layout(location = 8) in vec4 modelInst4;
layout(location = 5) in mat4 modelInst;
//layout(location = 0) in vec3 normal;
//layout(location = 0) in vec3 uvs;
//layout(location = 0) in vec3 position;

//out vec2 UVs;
out VS_OUT{
	float instanceID;
	float vertexID;
	float Height;
	vec3 Normals;
	vec3 FragPos;
	mat4 modelMat;

	float Time;
} gs_in;



uniform float time;
uniform bool isAnimated;
uniform mat4 WVM;
uniform mat4 Bones[100];

void main()
{
	vec4 objectpos = vec4(position, 1.0);
	if (isAnimated==true)
	{
		mat4 BoneTransform;
		BoneTransform = Bones[bonesID[0]] * Weights[0];
	/*	BoneTransform += Bones[bonesID[1]] * Weights[1];
		BoneTransform += Bones[bonesID[2]] * Weights[2];
		BoneTransform += Bones[bonesID[3]] * Weights[3];*/
		objectpos = BoneTransform * vec4(position, 1.0);
	}
	else
	{
		float timeOffset = (gl_InstanceID % 6)/5.0;
		gs_in.Time = mod(time/2+ timeOffset, 1.0);
		//float Time = (time + (gl_InstanceID % 6)/5.0)/2.0;
		if (gs_in.Time > 0.5)
			gs_in.Time = 1.0 - gs_in.Time;
		//objectpos = vec4(position, 1.0) + vec4((gl_VertexID+1)*Time,0,0,0);// + vec4(5*gl_InstanceID, 0, 5*gl_InstanceID,0);
	}
	gl_Position = objectpos;
	
	gs_in.modelMat = modelInst;
	gs_in.instanceID = gl_InstanceID;
	gs_in.vertexID = gl_VertexID;
	gs_in.Normals = normals;
	gs_in.FragPos = position;
	gs_in.Height = 1;// modelInst.y;

	//InstanceID2 = 1;
	//UVs = uvs;
}