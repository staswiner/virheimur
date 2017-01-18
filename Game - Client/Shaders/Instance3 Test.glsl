#version 400 core
layout(points) in;
layout(triangle_strip, max_vertices = 7) out;

in VS_OUT{
	float instanceID;
float vertexID;
float Height;
vec3 FragPos;
mat4 modelMat;

float Time;
} gs_in[];
in mat4 ModelMat[];

out GS_OUT{
	float instanceID;
float vertexID;
float Height;
vec3 Normals;
vec3 FragPos;
vec4 UV;
float index;
} gs_out;

uniform mat4 WVM;
uniform mat4 Animation[25];
uniform vec3 cameraPos;

void firstLayer();
void secondLayer();
void TransferData()
{
	gs_out.instanceID = gs_in[0].instanceID;
	gs_out.vertexID = gs_in[0].vertexID;
	gs_out.Height = gs_in[0].Height;
	gs_out.FragPos = gs_in[0].FragPos;
}
vec3 GetNormal(vec3 v1, vec3 v2, vec3 v3)
{
	vec3 a = v1 - v2;
	vec3 b = v3 - v2;
	return normalize(cross(a, b));
}
void main()
{
	vec4 offset[3];
	offset[0] = vec4(0, 0, 0, 0);
	offset[1] = vec4(0.5, 0, 0, 0);
	offset[2] = vec4(0, 3, 0, 0);
	for (int i = 0; i < 3; i++)
	{
		gl_Position = gl_in[0].gl_Position + offset[i];
		EmitVertex();
	}
	firstLayer();
	EndPrimitive();
	//vec3 StartPoint = vec3(gs_in[0].modelMat * gl_in[0].gl_Position);
	//if (length(-cameraPos - StartPoint) < 200)
	//{
	//	//firstLayer();
	//}
	//else if (length(-cameraPos - StartPoint) < 500)
	//{
	//	//secondLayer();
	//}
	//else
	//{

	//}
//	EndPrimitive();

}
void firstLayer()
{
	vec4 offset[7];
	offset[0] = vec4(0, 0, 0, 0);
	offset[1] = vec4(0.5, 0, 0, 0);
	offset[2] = vec4(0, 3, 0, 0);
	offset[3] = vec4(0.5, 2, 0, 0);
	offset[4] = vec4(0, 6, 0, 0);
	offset[5] = vec4(0.5, 4, 0, 0);
	offset[6] = vec4(0, 10, 0, 0);
	//
	if (mod(gs_in[0].instanceID, 2) == 0)
	{
		offset[0] = vec4(2, 5, 0.5, 0);
		offset[1] = vec4(1, 3, 0.5, 0);
		offset[2] = vec4(0.5, 0, 0.5, 0);
		offset[3] = vec4(0, 0, 0.5, 0);
		offset[4] = vec4(0, 3, -0.5, 0);
		offset[5] = vec4(-0.5, 3, -0.5, 0);
		offset[6] = vec4(-0.5, 7, -0.5, 0);
	}


	vec4 v[7];

	mat4 test = gs_in[0].modelMat;
	vec4 FractalUV = /*gs_in[0].modelMat **/ (gl_in[0].gl_Position);
	//gs_out.UV = FractalUV;
	//vec4 FractalLocation = texture(Fractal, (FractalUV.xz+100.0) / 200.0f);
	//if (FractalLocation.x > 0.9)
	//	return;

	//int Instance = int(mod(int(gs_in[0].instanceID), 2));
	//for (int i = 0; i < 7; i++)
	//{
	//	v[i] = (gl_in[0].gl_Position + offset[i]);
	//	for (int j = 0; j < 1; j++)
	//	{
	//		v[i] = Animation[int(0)] * v[i];
	//	}
	//	v[i] = gs_in[0].modelMat * v[i];
	//}

	//vec3 normals[5];
	//for (int i = 0; i < 5; i++)
	//{
	//	normals[i] = GetNormal(vec3(v[i]), vec3(v[i + 1]), vec3(v[i + 2]));
	//}

	//for (int i = 0; i < 7; i++)
	//{
	//	gl_Position = WVM * v[i];
	//	TransferData();
	//	gs_out.Normals = normals[0];
	//	gs_out.index = float(i);
	//	EmitVertex();
	//}

}
//void secondLayer()
//{
//	vec4 offset[3];
//	offset[0] = vec4(0, 0, 0, 0);
//	offset[1] = vec4(0.5, 0, 0, 0);
//	offset[2] = vec4(0, 10, 0, 0);
//	vec4 v[3];
//
//	vec4 FractalUV = gs_in[0].modelMat * (gl_in[0].gl_Position);
//	gs_out.UV = FractalUV;
//	//vec4 FractalLocation = texture(Fractal, (FractalUV.xz + 100.0) / 200.0f);
//	//if (FractalLocation.x > 0.9)
//	//	return;
//	int Instance = int(mod(int(gs_in[0].instanceID), 2));
//	for (int i = 0; i < 3; i++)
//	{
//		v[i] = (gl_in[0].gl_Position + offset[i]);
//		for (int j = 0; j < 1; j++)
//		{
//			v[i] = Animation[int(FractalLocation * 24)] * v[i];
//		}
//		v[i] = gs_in[0].modelMat * v[i];
//	}
//
//	vec3 normals[1];
//	for (int i = 0; i < 1; i++)
//	{
//		normals[i] = GetNormal(vec3(v[i]), vec3(v[i + 1]), vec3(v[i + 2]));
//	}
//
//	for (int i = 0; i < 3; i++)
//	{
//		gl_Position = WVM * v[i];
//		TransferData();
//		gs_out.Normals = normals[0];
//		gs_out.index = 3 * float(i);
//		EmitVertex();
//	}
//}