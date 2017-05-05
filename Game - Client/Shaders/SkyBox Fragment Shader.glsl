#version 400 core
in vec3 TexCoords;
out vec4 color;

uniform samplerCube skybox;

void main()
{    
	color = texture(skybox, TexCoords);
	color = vec4(0.7, 0.7, 0.95, 1.0);
}

  