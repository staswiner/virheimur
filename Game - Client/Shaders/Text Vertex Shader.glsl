#version 400 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	vec2 vertexGL = vertex.xy;
    gl_Position = projection * view * model * vec4(vertexGL.x, vertex.y, 0.0, 1.0);
    TexCoords = vertex.zw;
}  