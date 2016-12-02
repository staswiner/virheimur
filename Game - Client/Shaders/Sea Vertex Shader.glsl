#version 400 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;

out VS_OUT
{
	vec4 clipSpace;
	vec3 toCameraVector;
	vec2 TexCoords;
	vec3 fromLightVector;
	vec3 worldPos;
}vs_out;

uniform mat4 projectionMat;
uniform mat4 viewMat;
uniform mat4 modelMat;
uniform vec3 cameraPosition;
uniform vec3 LightPos;
uniform float WaveOffset;

const vec4 SeaLevel = vec4(0,1,0,0);


const float tiling = 20.0;
void main()
{
	vec3 WavePosition = vec3(position.x, sin(WaveOffset * 10.0f) / 100.0f, position.z);
	vec4 WorldPosition = modelMat * vec4(position, 1.0);

	vs_out.worldPos = vec3(WorldPosition/WorldPosition.w);
	vs_out.clipSpace = projectionMat * viewMat * modelMat * vec4(position, 1.0);
	gl_Position = vs_out.clipSpace;
	vs_out.toCameraVector = cameraPosition + vec3(WorldPosition.xyz);
	vs_out.TexCoords = vec2(texCoords.x, texCoords.y) * tiling;
	vs_out.fromLightVector = WorldPosition.xyz - LightPos;
}