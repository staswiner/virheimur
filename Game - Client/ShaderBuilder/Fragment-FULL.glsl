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
struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 emissive;
	float shininess;
};
uniform sampler2D Texture[5];
uniform sampler2D NormalMap[5];
uniform sampler2D Dispose;
uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform Material material;
out vec4 color;
vec3 CalcNormal()
		{
			vec3 Normal = normalize(fs_in.Normals);
			return Normal;
		}
vec3 AddLight(Material material, vec3 LightColor, vec3 LightDir
)
{
	// Mathematics
	vec3 toCameraVector = normalize(fs_in.FragPos - cameraPos);
	
	// Light
	vec3 ambient = LightColor * material.ambient;
	vec3 norm = CalcNormal();
	vec3 textnorm = norm;
	float diff = max(dot(textnorm, LightDir), 0.0);
	vec3 diffuse = diff * material.diffuse * LightColor;

	//  specular
	////vec3 reflectedLight = reflect(normalize(lightDir), norm);//phong
	vec3 reflectedLight = normalize(LightDir - normalize(toCameraVector));//blinn-phong
	////float spec = pow(max(dot(normalize(toCameraVector.xz), reflectedLight.xz), 0.0), shineDamper);//phong
	float spec = pow(max(dot(norm, reflectedLight), 0.0), int(material.specular * 64));//blinn-phong
	vec3 specular = spec * LightColor;
	//	float shadow = ShadowCalculation(fs_in.LightFragPos,LightDir, textnorm);    "
	// Enable Shadows
	//	shadow = 0;
	vec3 emissive = material.emissive;
	vec3 Light = (diffuse + (specular + ambient)) + emissive*diffuse;
//vec3 Light = diffuse;

	return Light;
}
void main()
{
	vec3 LightColor = vec3(1.0, 0.9, 0.7);
	vec3 lightDir = normalize(lightPos - fs_in.FragPos);
vec3 TotalColor = AddLight(material, LightColor, lightDir
);
	float near = 0.1f;
	float far = 1000.0f;
	float depth = gl_FragCoord.z;
	float Distance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));

	color = vec4(TotalColor, 1);
	float gamma = 1.2;
	color.rgb = pow(color.rgb, vec3(1.0/gamma));
	//color.rgb = CalcNormal(NormalMap[0]);
}
