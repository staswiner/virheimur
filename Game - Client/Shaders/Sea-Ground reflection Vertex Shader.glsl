#version 400 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
//layout (location = 2) in vec2 texCoord;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out vec4 FragPosLightSpace;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;
uniform mat4 worldSpace;

vec4 SeaLevel = vec4(0, 1, 0, 0);
void main()
{
	/*vec4 gl_Position = vec4(position.x, position.y, 0.0, 1.0f)*/
	vec4 WorldPosition = model * vec4(position, 1.0f);
	gl_Position = worldSpace * vec4(position, 1.0f);

	gl_ClipDistance[0] = dot(SeaLevel, WorldPosition);
	TexCoord = vec2(position.x, position.z) / 20.0f;
	Normal = normal;
	FragPos = vec3(model * vec4(position, 1.0f));
	FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0f);
}