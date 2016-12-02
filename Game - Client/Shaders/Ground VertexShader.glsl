#version 400 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;
//layout (location = 2) in vec2 texCoord;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out vec4 FragPosLightSpace;
out vec3 WorldPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;
uniform mat4 worldSpace;

void main()
{
	gl_Position = worldSpace * vec4(position, 1.0f);
	TexCoord = vec2(position.x, position.z) / 20.0f;
	Normal = normal;
	vec4 WorldPos4 = model * vec4(position, 1.0f);
	WorldPos4 = WorldPos4 / WorldPos4.w;
	WorldPos = vec3(WorldPos4);
	FragPos = vec3(model * vec4(position, 1.0f));
	FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0f);
} 