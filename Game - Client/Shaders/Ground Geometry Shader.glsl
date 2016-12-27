#version 400 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;


in VS_OUT{
vec2 UVs;
vec3 Normals;
vec3 FragPos;
}vs_in[];

out GS_OUT{
vec2 UVs;
vec3 Normals;
vec3 FragPos;
vec3 tangent;
}gs_out;

uniform mat4 WVM;

void TransferData(int i)
{
	gl_Position = gl_in[i].gl_Position;
	gs_out.UVs = vs_in[i].UVs;
	gs_out.Normals = vs_in[i].Normals;
	gs_out.FragPos = vs_in[i].FragPos;
	return;
}
void CalculateTangent()
{
	// MBT::
	vec3 Edge1 = vs_in[1].FragPos - vs_in[0].FragPos;
	vec3 Edge2 = vs_in[2].FragPos - vs_in[0].FragPos;

	float DeltaU1 = vs_in[1].UVs.x - vs_in[0].UVs.x;
	float DeltaV1 = vs_in[1].UVs.y - vs_in[0].UVs.y;
	float DeltaU2 = vs_in[2].UVs.x - vs_in[0].UVs.x;
	float DeltaV2 = vs_in[2].UVs.y - vs_in[0].UVs.y;

	float f = 1.0f / (DeltaU1 * DeltaV2 - DeltaU2 * DeltaV1);

	vec3 Tangent, Bitangent;

	Tangent.x = f * (DeltaV2 * Edge1.x - DeltaV1 * Edge2.x);
	Tangent.y = f * (DeltaV2 * Edge1.y - DeltaV1 * Edge2.y);
	Tangent.z = f * (DeltaV2 * Edge1.z - DeltaV1 * Edge2.z);

	Bitangent.x = f * (-DeltaU2 * Edge1.x - DeltaU1 * Edge2.x);
	Bitangent.y = f * (-DeltaU2 * Edge1.y - DeltaU1 * Edge2.y);
	Bitangent.z = f * (-DeltaU2 * Edge1.z - DeltaU1 * Edge2.z);

	gs_out.tangent = vec3(WVM*vec4(Tangent,0.0));

}
void main()
{
	for (int i = 0; i < 3; i++)
	{
		TransferData(i);
		//// MBT::
		//	vec3 Edge1 = v1.m_pos - v0.m_pos;
		//	vec3 Edge2 = v2.m_pos - v0.m_pos;
		//
		//	float DeltaU1 = v1.m_tex.x - v0.m_tex.x;
		//	float DeltaV1 = v1.m_tex.y - v0.m_tex.y;
		//	float DeltaU2 = v2.m_tex.x - v0.m_tex.x;
		//	float DeltaV2 = v2.m_tex.y - v0.m_tex.y;
		EmitVertex();
	}
	EndPrimitive();
}