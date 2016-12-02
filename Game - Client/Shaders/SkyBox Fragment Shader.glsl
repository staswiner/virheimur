#version 400 core
in vec3 TexCoords;
out vec4 color;

uniform samplerCube skybox;
uniform float colorvar;

void main()
{    
	color = texture(skybox, TexCoords);// *vec4(1 - colorvar, 1, colorvar, 1);
	color = vec4(0.95, 0.95, 0.65, 1.0);
}

  