#version 400 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	vec2 vertexGL = (vertex.xy - vec2(400,300)) / vec2(400,300);
	vertexGL = vertex.xy;
	vec4 position = projection * view * model * vec4(vertexGL.xy, 0.0, 1.0);
    gl_Position = position;// / position.w;
	
    TexCoords = vertex.zw;
}  