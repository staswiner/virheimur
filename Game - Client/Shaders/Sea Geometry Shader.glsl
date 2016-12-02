#version 400 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 6) out;

in VS_OUT
{
	vec4 clipSpace;
	vec3 toCameraVector;
	vec2 TexCoords;
	vec3 fromLightVector;
	vec3 worldPos;
}gs_in[];


out vec4 clipSpace;
out vec3 toCameraVector;
out vec2 TexCoords;
out vec3 fromLightVector;
out vec3 WorldPos;


void AssignTransferData(int i)
{
	clipSpace = gs_in[i].clipSpace;
	toCameraVector = gs_in[i].toCameraVector;
	TexCoords = gs_in[i].TexCoords;
	fromLightVector = gs_in[i].fromLightVector;
	WorldPos = gs_in[i].worldPos;
}

void main() {    
    gl_Position = gl_in[0].gl_Position;
	AssignTransferData(0);
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
	AssignTransferData(1);
    EmitVertex();

	gl_Position = gl_in[2].gl_Position;
	AssignTransferData(2);
    EmitVertex();

	EndPrimitive();

}  