#version 400 core
layout (location = 0) in vec2 position;
out vec2 TexCoords;

void main()
{
	gl_Position = vec4(position.x, position.y, 0.0, 1.0);
	float x,y;
	x = position.x;
	y = position.y;
	if (position.x == -1.0f) {
		x = 0;
	}
	if (position.y == -1.0f) {
		y = 0;
	}
    TexCoords = vec2(x, y);
}  