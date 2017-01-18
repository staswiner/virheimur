#version 400 compatibility

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 uvs;
layout(location = 3) in ivec4 bonesID;
layout(location = 4) in vec4 Weights;


out VS_OUT{
vec2 UVs;
vec3 Normals;
vec3 FragPos;
vec3 LightFragPos;
}vs_out;

//varying vec3 varColor;
//flat out int InstanceID;

uniform bool isAnimated;
uniform mat4 WVM;
uniform mat4 LightViewMatrix;
uniform mat4 Model;

uniform int BoneNum;
uniform mat4 Bones[100];

void main()
{
	vec4 objectpos = vec4(position, 1.0);
	if (isAnimated==true)
	{
		mat4 BoneTransform = mat4(0);
		//BoneTransform += Bones[bonesID[0]] * Weights[0];
		for(int i = 0 ; i < 4; i++)
		{
			BoneTransform += Bones[bonesID[i]] * Weights[i];
		}

		objectpos = BoneTransform * vec4(position, 1.0);
	}
	//}
	//else
	//{
	//	objectpos = vec4(position, 1.0);
	//}

	gl_Position = WVM * objectpos;
	vs_out.UVs = vec2(uvs.x,1.0-uvs.y);
	vs_out.Normals = normals;
	vs_out.FragPos = vec3(Model * vec4(position,1));
	vec4 lFragPos = LightViewMatrix * vec4(vs_out.FragPos,1);
	vs_out.LightFragPos = vec3(lFragPos.xyz)/lFragPos.w; 
}