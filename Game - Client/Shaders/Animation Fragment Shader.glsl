#version 400 core

in vec2 UVs;
//flat in int InstanceID;
uniform sampler2D myTexture0;
uniform sampler2D myTexture1;
uniform bool isInstanced;
out vec4 color;


void main()
{   
	//color = texture(myTexture0, UVs);
	//if (isInstanced==true)
	//{
	//	//color = vec4(InstanceID % 4, 1, 1, 1);
	//}
	//else
	//{
		color = vec4(0, 1, 0, 1);
	//}
	//color = vec4(0.0,1.0,1.0,1.0);
}

  