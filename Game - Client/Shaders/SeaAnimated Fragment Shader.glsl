#version 400 core


in GS_OUT{
	float instanceID;
	float vertexID;
	float Height;
	float index;
	vec3 Normals;
	vec3 FragPos;
} gs_out;
//in vec2 UVs;

//uniform sampler2D myTexture0;
//uniform sampler2D myTexture1;
out vec4 color;


void main()
{
//{   // all syntax correct
	vec3 lightPos = vec3(30, 30, 30);
	vec3 norm = normalize(gs_out.Normals);
	vec3 lightDir = normalize(lightPos - gs_out.FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(0.5) + vec3(0.5);

	vec3 result = diffuse * vec3(0, 0, 1);
	float vertexb2=mod(gs_out.instanceID,8);
	color = vec4(result,1);
	//color = vec4(0, (0 + vertexb2*4.0 + gs_out.vertexID*5.0) / 255.0, (100.0 + vertexb2 + gs_out.vertexID*5.0) / 255.0, 1);
//	color = vec4(1);
}

  