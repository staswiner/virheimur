#version 400 core

layout(location = 0) in vec3 position;
layout(location = 3) in ivec4 bonesID;
layout(location = 4) in vec4 Weights;
//layout(location = 0) in vec3 normal;
//layout(location = 0) in vec3 uvs;
//layout(location = 0) in vec3 position;


uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 Bones[100];

void main()
{
	mat4 BoneTransform;
	//vec4 w = Weights;

	BoneTransform = Bones[bonesID[0]] * Weights[0];
	//BoneTransform += Bones[bonesID[1]] * Weights[1];
	//BoneTransform += Bones[bonesID[2]] * Weights[2];
	//BoneTransform += Bones[bonesID[3]] * Weights[3];
	//BoneTransform = Bones[0];


	//vec4 bs = BoneTransform * w;
	//BoneTransform += Bones[BoneIDs[1]] * Weights[1];
	//BoneTransform += Bones[BoneIDs[2]] * Weights[2];
	//BoneTransform += Bones[BoneIDs[3]] * Weights[3];

	gl_Position = projection * view * model * BoneTransform * vec4( position, 1.0 );
}