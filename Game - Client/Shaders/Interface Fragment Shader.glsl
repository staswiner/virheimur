#version 400 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D ourTexture;

void main()
{    
    color = texture(ourTexture, TexCoords);
	//if (color.x > 0.9 && color.y > 0.9 && color.z > 0.9)
	//{
	////	color = vec4(1,1,1,0);
	//}
	//color = vec4(1,0,0,0);
}
