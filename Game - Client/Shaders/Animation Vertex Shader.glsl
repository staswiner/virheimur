#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 uvs;
layout(location = 3) in ivec4 bonesID;
layout(location = 4) in vec4 Weights;
//layout(location = 0) in vec3 normal;
//layout(location = 0) in vec3 uvs;
//layout(location = 0) in vec3 position;

out VS_OUT{
vec2 UVs;
vec3 Normals;
vec3 FragPos;
}vs_out;
varying vec3 varNormal;

//varying vec3 varColor;
//flat out int InstanceID;

uniform bool isAnimated;
uniform mat4 WVM;
uniform mat4 Model;

uniform int BoneNum;
uniform mat4 Bones[100];

void main()
{
	vec4 objectpos;
	if (isAnimated==true)
	{
		mat4 BoneTransform;
		for(int i = 0 ; i < BoneNum; i++)
		{
			BoneTransform += Bones[bonesID[i]] * Weights[i];
		}

	
		objectpos = BoneTransform * vec4(position, 1.0);
	}
	else
	{
		objectpos = vec4(position, 1.0);
	}

	gl_Position = WVM * objectpos;
	vs_out.UVs = vec2(uvs.x,1.0-uvs.y);
	vs_out.Normals = normals;
	vs_out.FragPos = vec3(Model * vec4(position,1));
	varNormal = normals;

	//vec3 lightDirection = vec3(30, 30, 0);
	//vec4 modelViewPos = vec4(position, 1.0);
	//vec3 normal = normalize(normals);
	//float dotValue = max(dot(normal, lightDirection), 0.0);
	//varColor = vec3(dotValue);// *dotValue;

//	UVs = uvs;

}