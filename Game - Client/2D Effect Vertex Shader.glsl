#version 400 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 uvs;
out vec2 UVs;

uniform mat4 WVM;

void main()
{
	gl_Position = WVM * vec4(position, 1.0);
    UVs = uvs;
}  