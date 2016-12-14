#version 400 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in VS_OUT{
	float VertexID;
} gs_in[];

out GS_OUT{
	vec3 VertexID;
} gs_out;

void main()
{
	//
	vec3 vertexOUT;
	vertexOUT = vec3(gs_in[0].VertexID, gs_in[1].VertexID, gs_in[2].VertexID);
	
	for (int i = 0; i < 3; i++)
	{
		gl_Position = gl_in[i].gl_Position;
		gs_out.VertexID = vertexOUT;
		EmitVertex();
	}
	EndPrimitive();

}
