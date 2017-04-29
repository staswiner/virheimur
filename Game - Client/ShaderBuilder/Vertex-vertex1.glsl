#version 400 compatibility 
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 uvs;
layout(location = 3) in ivec4 bonesID;
layout(location = 4) in vec4 Weights;

out float gl_ClipDistance[1];
out VS_OUT{
vec2 UVs;
vec3 Normals;
vec3 FragPos;
vec3 LightFragPos;
vec4 clipSpace;
}vs_out;

uniform bool isAnimated;
uniform mat4 WVM;
uniform mat4 LightMatrix;
uniform mat4 Model;

uniform int BoneNum;
uniform mat4 Bones[100];


void main()
{
	vec4 objectpos = vec4(position, 1.0);
	vec4 normalpos = vec4(normals,0.0);
	if (isAnimated == true)
	{
		mat4 BoneTransform = mat4(0);
		//BoneTransform += Bones[bonesID[0]] * Weights[0];
		for (int i = 0; i < 4; i++)
		{
			BoneTransform += Bones[bonesID[i]] * Weights[i];
		}

		objectpos = BoneTransform * vec4(position, 1.0);
		normalpos = BoneTransform * vec4(normals,0.0); 
	}
	vec4 FragPos4 = Model * objectpos;
	vs_out.FragPos = vec3(FragPos4.xyz/FragPos4.w);

	vs_out.clipSpace = WVM * objectpos;

	gl_Position = vs_out.clipSpace;
	vs_out.UVs = vec2(uvs.x, 1.0 - uvs.y);
	vec4 Normals4 = Model * normalpos;
	vs_out.Normals = vec3( Normals4 );
	

	vec4 lFragPos = LightMatrix * vec4(vs_out.FragPos, 1);
	vs_out.LightFragPos = vec3(lFragPos.xyz) / lFragPos.w;


}