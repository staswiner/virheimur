#version 400 core

in float vertexb;
in float vertexc;
flat in int InstanceID;
//in vec2 UVs;

//uniform sampler2D myTexture0;
//uniform sampler2D myTexture1;
out vec4 color;


void main()
{   
	//color = texture(myTexture0, UVs);
	//if (isInstanced==true)
	//{
	//	//color = vec4(1, 1, 1, 1);
	//}
	float vertexb2=mod(vertexb,4);
		color = vec4(0, (100.0+vertexb2*4.0 + vertexc*5.0)/255.0, (10.0+vertexb2 + vertexc*5.0)/255.0, 1);

}

  