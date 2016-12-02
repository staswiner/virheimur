#version 400 core
layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uvs;
out vec2 TexCoords;

//uniform mat4 projection;
//uniform mat4 view;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


uniform vec2 truesize;
uniform vec2 topleft;
uniform vec2 botright;

void main()
{
	gl_Position = projection * view * model * vec4(vertexGL.x, vertex.y, 0.0, 1.0);
	float x, y;
	vec2 CroppedUV = vec2((botright.x - topleft.x )/truesize.x, (botright.y - topleft.y) / truesize.y);
	CroppedUV += vec2(topleft.x / truesize.x, topleft.y / truesize.y);
	vec2 UVs = vec2(uvs.x*CroppedUV.x, uvs.y*CroppedUV.y);
	TexCoords = vec2(UVs.x, 1 - UVs.y);
}