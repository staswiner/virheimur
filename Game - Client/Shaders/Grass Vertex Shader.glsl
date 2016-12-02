#version 400 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 posOffset;
layout (location = 4) in float grassTime;


out VS_OUT{
	vec2 texCoords;
	vec3 Normal;
	vec3 FragPos;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 worldSpace;
uniform float time;

void main()
{
	vec3 NewPos = position + posOffset;
	float vibratingPower = pow(2,position.y) / 5.0f;
	vec4 vibratingPos = vec4(NewPos.x + vibratingPower * sin(time + grassTime),NewPos.y,NewPos.z + vibratingPower * sin(time + grassTime ), 1.0f );
    gl_Position = worldSpace * vibratingPos;
    vs_out.texCoords = vec2(texCoord.x, 1.0 - texCoord.y);

	vs_out.Normal = vec3(model * vec4(normal, 0.0));
	vs_out.FragPos = vec3(model * vec4(position, 1.0f));
}