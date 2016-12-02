#version 400 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;


out VS_OUT{
	vec2 texCoords;
	vec3 Normal;
	vec3 FragPos;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 worldSpace;

vec4 SeaLevel = vec4(0,1.0,0,0);
void main()
{
    gl_Position = worldSpace * vec4(position, 1.0f);
	vec4 worldPosition = model * vec4(position, 1.0f);
    vs_out.texCoords = vec2(texCoord.x, 1.0 - texCoord.y);

	gl_ClipDistance[0] = dot(SeaLevel, WorldPosition);

	vs_out.Normal = vec3(model * vec4(normal, 0.0));
	vs_out.FragPos = vec3(model * vec4(position, 1.0f));
}