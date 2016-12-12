#version 400 core

//in GS_OUT{
//	float VertexID[3];
//} fs_in;
out vec4 color;


void main()
{    
	//color = vec4(fs_in.VertexID[0], fs_in.VertexID[1], fs_in.VertexID[2],1);
	color = vec4(1.0);

}

  