#version 400 core

layout(location = 0) in vec3 position;
layout(location = 3) in uint bonesID;
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
	mat4 BoneTransform = Bones[BoneIDs] * Weights;
	//BoneTransform += Bones[BoneIDs[1]] * Weights[1];
	//BoneTransform += Bones[BoneIDs[2]] * Weights[2];
	//BoneTransform += Bones[BoneIDs[3]] * Weights[3];

	gl_Position = projection * view * model * BoneTransform * vec4( position, 1.0 );
}