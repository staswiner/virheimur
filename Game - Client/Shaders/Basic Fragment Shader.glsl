#version 400 core

uniform vec3 ucolor;

out vec4 color;

void main()
{    
	color = vec4(ucolor, 1.0);
	//color = vec4(0.0,1.0,1.0,1.0);
}

  