#version 400 core
layout(points) in;
layout(triangle_strip, max_vertices = 6) out;
//
in VS_OUT{
	float instanceID;
	float vertexID;
	float Height;
	vec3 Normals;
	vec3 FragPos;
	mat4 modelMat;

	float Time;
} gs_in[];

out GS_OUT{
	float instanceID;
	float vertexID;
	float Height;
	vec3 Normals;
	vec3 FragPos;
	float index;
} gs_out;
uniform mat4 WVM;
uniform mat4 Animation[2];
uniform vec3 cameraPos;
uniform float SlowTime;
//
void TransferData()
{
	gs_out.instanceID=gs_in[0].instanceID;
	gs_out.vertexID	 =gs_in[0].vertexID;
	gs_out.Height	 =gs_in[0].Height;
	gs_out.Normals	 =gs_in[0].Normals;
	gs_out.FragPos	 =gs_in[0].FragPos;
}
//float rand(vec2 co)
//{
//	return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
//}
vec3 GetNormal(vec3 v1, vec3 v2, vec3 v3)
{
	vec3 a = v1 - v2;
	vec3 b = v3 - v2;
	return normalize(cross(a, b));
}
void firstLayer();
void secondLayer();
void main()
{
 
	vec3 StartPoint = vec3(gs_in[0].modelMat * gl_in[0].gl_Position);
	if (length(-cameraPos - StartPoint) < 200)
	{
		firstLayer();
	}
	//else// if (length(-cameraPos - StartPoint) < 300)
	//{
	//	secondLayer();
	//}

}
void firstLayer()
{
	vec4 offset[6];
	int Instance = int(mod(int(gs_in[0].instanceID ), 2));
	float yRise;
	Instance == 0 ? yRise = -1 : yRise = 1;
	//yRise = 0;
	yRise *= sin(radians(mod(SlowTime,360)));
	offset[0] = vec4(0, yRise, 0, 0);
	offset[1] = vec4(1, -yRise, 0, 0);
	offset[2] = vec4(0, -yRise, 1, 0);
	offset[3] = vec4(1, -yRise, 0, 0);
	offset[4] = vec4(0, -yRise, 1, 0);
	offset[5] = vec4(1, yRise, 1, 0);

	vec4 v[6];
	for (int i = 0; i < 6; i++)
	{
		v[i] = gs_in[0].modelMat * (gl_in[0].gl_Position + offset[i]);
	}
	//vec3 normals[1];
	//for (int i = 0; i < 1; i++)
	//{
	//	normals[i] = GetNormal(vec3(v[i]), vec3(v[i+1]), vec3(v[i+2]));
	//}
	//
	vec3 normals[1];
	normals[0] = GetNormal(vec3(v[0]), vec3(v[0 + 1]), vec3(v[0 + 2]));
	for (int triangle = 0; triangle < 2; triangle++)
	{
		for (int i = triangle*3; i < (triangle+1)*3; i++)
		{
			gl_Position = WVM * v[i];
			TransferData();
			gs_out.Normals = normals[0];
			gs_out.index = float(i);
			EmitVertex();
		}
		EndPrimitive();
	}
}
void secondLayer()
{
	vec4 offset[3];
	offset[0] = vec4(0, 0, 0, 0);
	offset[1] = vec4(0.5, 0, 0, 0);
	offset[2] = vec4(0, 10, 0, 0);
	vec4 v[3];

	int Instance = int(mod(int(gs_in[0].instanceID), 8));
	for (int i = 0; i < 3; i++)
	{
		v[i] = (gl_in[0].gl_Position + offset[i]);
		for (int j = 0; j < 1; j++)
		{
			v[i] = Animation[Instance] * v[i];
		}
		v[i] = gs_in[0].modelMat * v[i];
	}

	vec3 normals[1];
	for (int i = 0; i < 1; i++)
	{
		normals[i] = GetNormal(vec3(v[i]), vec3(v[i + 1]), vec3(v[i + 2]));
	}

	for (int i = 0; i < 3; i++)
	{
		gl_Position = WVM * v[i];
		TransferData();
		gs_out.Normals = normals[0];
		gs_out.index = 3 * float(i);
		EmitVertex();
	}
}
//mat4 Rotation(vec3 Rot)
//{
//	mat4 rotMat = {
//		cos(Rot[1])*cos(Rot[2]),-cos[Rot[1]]*sin[Rot[2]], sin[Rot[1]], 0,
//		
//		sin[Rot[0]]*sin[Rot[1]]*cos[Rot[2]]+cos[Rot[0]]*sin[Rot[2]],
//		-sin[Rot[0]]*sin[Rot[1]]*sin[Rot[2]], -sin[Rot[0]]*sin[Rot[1]],0,
//		
//		-cos[Rot[0]]*sin[Rot[1]]*cos[Rot[2]]+sin[Rot[0]]*sin[Rot[2]],
//		cos[Rot[0]]*sin[Rot[0]]*sin[Rot[2]]+sin[Rot[0]]*cos[Rot[2]],cos[Rot[0]]*cos[Rot[1]],0,
//	
//		0,0,0,1
//	}
//}