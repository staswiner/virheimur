#version 400 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;
//
//in VS_OUT{
//	float instanceID;
//	float vertexID;
//	float Height;
//	vec3 Normals;
//	vec3 FragPos;
//} gs_in[];

//out GS_OUT{
//	float instanceID;
//	float vertexID;
//	float Height;
//	vec3 Normals;
//	vec3 FragPos;
//} gs_out;
uniform mat4 WVM;

//
//void TransferData()
//{
//	gs_out.instanceID=gs_in[0].instanceID;
//	gs_out.vertexID	 =gs_in[0].vertexID;
//	gs_out.Height	 =gs_in[0].Height;
//	gs_out.Normals	 =gs_in[0].Normals;
//	gs_out.FragPos	 =gs_in[0].FragPos;
//}
void main()
{
	gl_Position = WVM * gl_in[0].gl_Position;
	EmitVertex();
	gl_Position = WVM * gl_in[1].gl_Position;
	EmitVertex();
	gl_Position = WVM * gl_in[2].gl_Position;
	EmitVertex();

	EndPrimitive();
}
//vec3 normal = GetNormal();
////1
//gl_Position = WVM * (gl_in[0].gl_Position + vec4(0, 0, 0, 0));
//TransferData();
//EmitVertex();
////2
//gl_Position = WVM * (gl_in[0].gl_Position + vec4(1, 0, 0, 0));
//TransferData();
//EmitVertex();
////3
//gl_Position = WVM * (gl_in[0].gl_Position + vec4(0, 0, 5, 0));
//TransferData();
//EmitVertex();
////4
//gl_Position = WVM * (gl_in[0].gl_Position + vec4(1, 0, 5, 0));
//TransferData();
//EmitVertex();
//5
//gl_Position = WVM * (gl_in[0].gl_Position + vec4(0, 0, 10, 0));
////TransferData();
//EmitVertex();
////6
//gl_Position = WVM * (gl_in[1].gl_Position + vec4(1, 0, 10, 0));
////TransferData();
//EmitVertex();
////7
//gl_Position = WVM * (gl_in[2].gl_Position + vec4(0, 0, 15, 0));
////TransferData();
//EmitVertex();

//}