#version 400 compatibility
layout(triangles) in;
layout(line_strip, max_vertices = 2) out;



in VS_OUT{
vec2 UVs;
vec3 Normals;
vec3 FragPos;
vec3 LightFragPos;
vec4 clipSpace;
}vs_in[];



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

void main()
{
	for (int i = 0; i < 2; i++)
	{
//GenerateLine(i);
		TransferData(i);
		CalculateTangent();
		EmitVertex();
	}
	EndPrimitive();
}
