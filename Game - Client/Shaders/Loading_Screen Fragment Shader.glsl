#version 400 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D ourTexture;

void main()
{    
    color = texture(ourTexture, TexCoords) * vec4(1,1,1,1);
	//color = vec4(1,0,0,0);
}

  