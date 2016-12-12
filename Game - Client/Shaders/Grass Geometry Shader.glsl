#version 400 core
layout(points) in;
layout(triangle_strip, max_vertices = 7) out;

in VS_OUT{
	vec2 texCoords;
	vec3 Normal;
	vec3 FragPos;
} gs_in[];

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform float time;
uniform float GravityHeight;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 worldSpace;

vec4 explode(vec4 position, vec3 normal)
{
	//float magnitude = 2.0f;
	//vec4 direction;
	//if (normal.z > 0.0f)
	//	direction = worldSpace * vec4(normal * time * magnitude, 1.0));
	//vec4 Gravity = worldSpace * vec4(0.0, -GravityHeight , 0.0, 1.0);
	//vec4 Up = worldSpace * vec4(0.0, 1.0, 0.0, 1.0);
	//vec4 newPosition = vec4(position + direction + Up, 1.0);// + Gravity;
	//vec4 newPositionWorldSpace = inverse(worldSpace) * newPosition;
	//if (newPositionWorldSpace.y < 0)
	//{
	//	return vec4(newPosition.x, 0, newPosition.z, newPosition.w);
	//}
	return position; // newPosition
}

vec3 GetNormal()
{
	vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
	return normalize(cross(a, b));
}
void TransferData(int i)
{
	TexCoords = gs_in[i].texCoords;
	Normal = gs_in[i].Normal;
	FragPos = gs_in[i].FragPos;
}
void main() {
	vec3 normal = GetNormal();
	//1
	gl_Position = gl_in[0].gl_Position + vec4(0, 0, 0, 0);
//	TransferData(0);
	EmitVertex();
	//2
	gl_Position = gl_in[0].gl_Position + vec4(1, 0, 0, 0);
//	TransferData(1);
	EmitVertex();
	//3
	gl_Position = gl_in[0].gl_Position + vec4(0, 0, 5, 0);

//	TransferData(2);
	EmitVertex();
	//4
	gl_Position = gl_in[0].gl_Position + vec4(1, 0, 5, 0);
	/*TexCoords = gs_in[2].texCoords;
	Normal = gs_in[2].Normal;
	FragPos = gs_in[2].FragPos;*/
	EmitVertex();
	//5
	gl_Position = gl_in[0].gl_Position + vec4(0, 0, 10, 0);
	//TexCoords = gs_in[2].texCoords;
	//Normal = gs_in[2].Normal;
	//FragPos = gs_in[2].FragPos;
	EmitVertex();
	//6
	gl_Position = gl_in[0].gl_Position + vec4(1, 0, 10, 0);
	//TexCoords = gs_in[2].texCoords;
	//Normal = gs_in[2].Normal;
	//FragPos = gs_in[2].FragPos;
	EmitVertex();
	//7
	gl_Position = gl_in[0].gl_Position + vec4(0, 0, 15, 0);
	//TexCoords = gs_in[2].texCoords;
	//Normal = gs_in[2].Normal;
	//FragPos = gs_in[2].FragPos;
	EmitVertex();

	EndPrimitive();
}