#version 400 core

in GS_OUT{
vec2 UVs;
vec3 Normals;
vec3 FragPos;
vec3 tangent;

}fs_in;
//flat in int InstanceID;
uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform sampler2D Texture2;
uniform sampler2D Texture3;//road texture
uniform sampler2D Texture4;//road normal texture
uniform sampler2D Texture5;//road bump texture
uniform float Texelation;
uniform mat4 WVM;
uniform mat4 Model;
uniform vec3 lightPos;
//uniform sampler2D Texture1;
//varying vec3 varColor;
out vec4 color;


vec3 CalcBumpedNormal()
{
	vec3 Normal = normalize(fs_in.Normals);
	vec3 Tangent = normalize(fs_in.tangent);
	Tangent = normalize(Tangent - dot(Tangent, Normal) * Normal);
	vec3 Bitangent = cross(Tangent, Normal);

	vec4 TexturedNormal = texture2D(Texture4, fs_in.UVs );
	TexturedNormal = (TexturedNormal*2.0 - 1.0);
	vec3 BumpMapNormal = vec3(TexturedNormal);

	vec3 NewNormal;
	mat3 TBN = mat3(Tangent, Bitangent, Normal);
	NewNormal = TBN * BumpMapNormal;
	NewNormal = normalize(NewNormal);
	return NewNormal;
}
void main()
{
	vec4 TexturedNormal = texture2D(Texture4, fs_in.UVs * Texelation);
	TexturedNormal = (TexturedNormal*2.0 - 1.0);
//	TexturedNormal = WVM*TexturedNormal;
//// MBT::
//	vec3 Edge1 = v1.m_pos - v0.m_pos;
//	vec3 Edge2 = v2.m_pos - v0.m_pos;
//
//	float DeltaU1 = v1.m_tex.x - v0.m_tex.x;
//	float DeltaV1 = v1.m_tex.y - v0.m_tex.y;
//	float DeltaU2 = v2.m_tex.x - v0.m_tex.x;
//	float DeltaV2 = v2.m_tex.y - v0.m_tex.y;
	// Light
	// old normal calculation
	//vec3 norm = normalize(fs_in.Normals);
	//new normal calculation
	vec3 norm = CalcBumpedNormal();
	vec3 textnorm = normalize(norm + vec3(TexturedNormal));
	vec3 lightDir = normalize(lightPos - fs_in.FragPos);
	float diff = max(dot(textnorm, lightDir), 0.0);
	vec3 diffuse = diff * diff * diff * vec3(1);
	float near = 0.1f;
	float far = 1000.0f;
	float depth = gl_FragCoord.z;
	float Distance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));
	vec4 color0 = texture2D(Texture0, fs_in.UVs * Texelation);
	vec4 color1 = texture2D(Texture1, fs_in.UVs * Texelation);
	vec4 color2 = texture2D(Texture2, fs_in.UVs);
	vec4 color3 = texture2D(Texture3, fs_in.UVs * Texelation);
	vec4 color5 = texture2D(Texture5, fs_in.UVs * Texelation);
	//if (color2.r < 0.5)
	if (abs(dot(norm, vec3(0, 1, 0))) > 0.8)
	{
		color = color3 * vec4(diffuse, 1) * color5 * 2;// *vec4(TexturedNormal.z, TexturedNormal.z, TexturedNormal.z, 1);
	}
	else
	{
		color = (color0 * dot(norm, vec3(0, 1, 0))) + (color1 * (1 - dot(norm, vec3(0, 1, 0)))) * vec4(diffuse, 1.0f);
	}



}

