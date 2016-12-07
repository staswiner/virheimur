#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 uvs;
layout(location = 3) in ivec4 bonesID;
layout(location = 4) in vec4 Weights;
layout(location = 5) in vec4 modelInst;
//layout(location = 0) in vec3 normal;
//layout(location = 0) in vec3 uvs;
//layout(location = 0) in vec3 position;

//out vec2 UVs;
out float vertexb;
out float vertexc;
flat out int InstanceID;

uniform float time;
uniform bool isAnimated;
uniform mat4 WVM;
uniform mat4 Bones[100];

void main()
{
	vec4 objectpos;
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
		float Time = mod(time/2+ timeOffset, 1.0);
		//float Time = (time + (gl_InstanceID % 6)/5.0)/2.0;
		if (Time > 0.5)
			Time = 1.0 - Time;
		objectpos = vec4(position, 1.0) + modelInst + vec4((gl_VertexID+1)*Time,0,0,0);// + vec4(5*gl_InstanceID, 0, 5*gl_InstanceID,0);
	}
//	vec4 Modelpos = modelInst*objectpos;
	gl_Position = WVM * objectpos;
	
	InstanceID = gl_InstanceID;
	vertexb = gl_InstanceID;
	vertexc = gl_VertexID;
	//InstanceID2 = 1;
	//UVs = uvs;

}