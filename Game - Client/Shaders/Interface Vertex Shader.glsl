#version 400 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uvs;
out vec2 TexCoords;

//uniform mat4 projection;
//uniform mat4 view;
uniform mat4 model;
uniform vec2 uvoffset;

void main()
{
	gl_Position = model * vec4(position.x, position.y, 0.0, 1.0);
	float x,y;
    TexCoords = vec2(uvs.x,1-uvs.y);
}  