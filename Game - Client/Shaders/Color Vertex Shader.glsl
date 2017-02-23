#version 400 compatibility

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 uvs;
layout(location = 3) in ivec4 bonesID;
layout(location = 4) in vec4 Weights;

uniform bool isAnimated;
uniform mat4 WVM;

uniform int BoneNum;	
uniform mat4 Bones[100];

void main()
{
	vec4 objectpos = vec4(position, 1.0);
	if (isAnimated==true)
	{
		mat4 BoneTransform = mat4(0);
		for(int i = 0 ; i < 4; i++)
		{
			BoneTransform += Bones[bonesID[i]] * Weights[i];
		}

		objectpos = BoneTransform * vec4(position, 1.0);
	}
	gl_Position = WVM * objectpos;

}