#version 400 compatibility

in GS_OUT{
vec2 UVs;
vec3 Normals;
vec3 FragPos;
vec4 clipSpace;
vec3 LightFragPos;
vec3 T;
vec3 B;
}fs_in;
//varying vec3 varNormalf;
struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
//flat in int InstanceID;
//uniform uint TextureCount;
uniform sampler2D Texture[5];
uniform sampler2D NormalMap[5];
uniform sampler2D Dispose;
uniform float Texelation;
uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform Material Wood;
//uniform sampler2D Texture1;
//varying vec3 varColor;
out vec4 color;

vec3 CalcNormal()
{
	vec3 Normal = normalize(fs_in.Normals);
	return Normal;
}
vec3 CalcBumpedNormal(in sampler2D normalTexture)
{
	vec3 Normal = CalcNormal();
	vec3 T = fs_in.T;
	T = normalize(T - dot(T, Normal) * Normal);
	vec3 B = cross(T, Normal);
	B = fs_in.B;

	vec4 TexturedNormal = texture2D(normalTexture, fs_in.UVs * Texelation);
	TexturedNormal = (TexturedNormal*2.0 - vec4(1.0));
	vec3 BumpMapNormal = vec3(TexturedNormal.xyz);// vec3(TexturedNormal.x, TexturedNormal.z, TexturedNormal.y);

	vec3 NewNormal;
	//mat3 TBN = mat3(vec3(1, 0, 0), vec3(0, 0, 1), Normal);
	mat3 TBN = mat3(T, B, Normal);
	NewNormal = TBN * BumpMapNormal;
	//NewNormal.x *= -1.0;
	//NewNormal.z *= -1.0;
	NewNormal = normalize(NewNormal);
	return NewNormal.xyz;
}
vec3 AddLight(in Material material,in vec3 LightColor, in vec3 LightDir, in sampler2D normalTexture)
{
	// Mathematics
	vec3 toCameraVector = normalize(fs_in.FragPos - cameraPos);

	// Light
	vec3 ambient = LightColor * material.ambient;
	vec3 norm = CalcBumpedNormal(normalTexture);
	float diff = max(dot(norm, LightDir), 0.0);
	vec3 diffuse = diff * material.diffuse * LightColor;

	//  specular
	////vec3 reflectedLight = reflect(normalize(lightDir), norm);//phong
	vec3 reflectedLight = normalize(LightDir - normalize(toCameraVector));//blinn-phong
	////float spec = pow(max(dot(normalize(toCameraVector.xz), reflectedLight.xz), 0.0), shineDamper);//phong
	float spec = pow(max(dot(norm, reflectedLight), 0.0), int(material.diffuse * 128.0));//blinn-phong
	vec3 specular = material.specular * spec * LightColor;
	vec3 Light = (diffuse + specular + ambient);
	return Light;
}
void main()
{ 
	vec3 LightColor = vec3(1.0,0.9,0.7);
	vec3 lightDir = normalize(lightPos - fs_in.FragPos);

	vec4 color0 = texture2D(Texture[0], fs_in.UVs * Texelation);
	vec3 TotalColor = vec3(color0) * AddLight(Wood,LightColor,lightDir,NormalMap[0]);
	
	float near = 0.1f;
	float far = 1000.0f;
	float depth = gl_FragCoord.z;
	float Distance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));

	color = vec4( AddLight(Wood,LightColor,lightDir,NormalMap[0]),1);
	//color = vec4(1.0,0,0,1.0);
}
