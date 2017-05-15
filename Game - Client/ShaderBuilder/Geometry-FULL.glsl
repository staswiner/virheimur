#version 400 compatibility
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;


in VS_OUT{
vec2 UVs;
vec3 Normals;
vec3 FragPos;
vec3 LightFragPos;
vec4 clipSpace;
}vs_in[];

out GS_OUT{
vec2 UVs;
vec3 Normals;
vec3 FragPos;
vec4 clipSpace;
vec3 LightFragPos;
vec3 T;
vec3 B;
}gs_out;
//varying out vec3 a;
uniform mat4 WVM;
//varying in vec3 varNormal[];
//varying vec3 varNormalf;
const float MAGNITUDE = 0.4f;
void GenerateLine(int i)
{
    gl_Position = gl_in[i].gl_Position;
    EmitVertex();
    gl_Position = gl_in[i].gl_Position + vec4(vs_in[i].Normals, 0.0f) * MAGNITUDE;
    EmitVertex();
}
void TransferData(in int i)
{
	gl_Position = gl_in[i].gl_Position;
	//gl_ClipDistance[0] = gl_in[i].gl_ClipDistance[0];
	gs_out.UVs = vs_in[i].UVs;
	gs_out.Normals = vs_in[i].Normals;
	gs_out.FragPos = vs_in[i].FragPos;
	gs_out.LightFragPos = vs_in[i].LightFragPos;
	gs_out.clipSpace = vs_in[i].clipSpace;
	//varNormalf = varNormal[i];
}
void CalculateTangent()
{
	// MBT::
	vec3 Edge1 = vs_in[1].FragPos - vs_in[0].FragPos;
	vec3 Edge2 = vs_in[2].FragPos - vs_in[0].FragPos;

	vec2 DeltaUV1 = vs_in[1].UVs - vs_in[0].UVs;
	vec2 DeltaUV2 = vs_in[2].UVs - vs_in[0].UVs;

	float f = 1.0f / (DeltaUV1.x * DeltaUV2.y - DeltaUV2.x * DeltaUV1.y);

	vec3 Tangent, Bitangent;

	Tangent.x = f * (DeltaUV2.y * Edge1.x - DeltaUV1.y * Edge2.x);
	Tangent.y = f * (DeltaUV2.y * Edge1.y - DeltaUV1.y * Edge2.y);
	Tangent.z = f * (DeltaUV2.y * Edge1.z - DeltaUV1.y * Edge2.z);

	Bitangent.x = f * (-DeltaUV2.x * Edge1.x - DeltaUV1.x * Edge2.x);
	Bitangent.y = f * (-DeltaUV2.x * Edge1.y - DeltaUV1.x * Edge2.y);
	Bitangent.z = f * (-DeltaUV2.x * Edge1.z - DeltaUV1.x * Edge2.z);

	Tangent = normalize(Tangent);
	Bitangent = normalize(Bitangent);
	gs_out.T = Tangent; // WVM * vector
	gs_out.B = Bitangent;

}
void main()
{
	for (int i = 0; i < 3; i++)
	{
//GenerateLine(i);
		TransferData(i);
		CalculateTangent();
		EmitVertex();
	}
	EndPrimitive();
}
