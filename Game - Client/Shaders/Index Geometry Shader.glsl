#version 400 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;
//
//in VS_OUT{
//	float VertexID;
//} gs_in[];
//
//out GS_OUT{
//	float VertexID[3];
//} gs_out;

void main()
{
	//float vertexOUT[3];
	/*for (int i = 0; i < 3; i++)
		vertexOUT[i] = gs_in[i].VertexID;
	*/
	//for (int i = 0; i < 3; i++)
	//{
		gl_Position = gl_in[0].gl_Position;
	//	gs_out.VertexID = vertexOUT; 
		EmitVertex();
		gl_Position = gl_in[1].gl_Position;
		//	gs_out.VertexID = vertexOUT; 
		EmitVertex();
		gl_Position = gl_in[2].gl_Position;
		//	gs_out.VertexID = vertexOUT; 
		EmitVertex();
	//}
	EndPrimitive();

}
