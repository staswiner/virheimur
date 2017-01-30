// shadertype=cg

#version 400 core

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
	float shininess;
};
//flat in int InstanceID;
uniform sampler2D Texture0;//grass
uniform sampler2D Texture1;//mountain
uniform sampler2D Texture2;//map path
uniform sampler2D Texture3;//reflection
uniform sampler2D Texture4;//road normal texture
uniform sampler2D Texture5;//road bump texture
uniform sampler2D Texture6;//road dark texture
uniform sampler2D Texture7;//texture normal texture
uniform sampler2D Texture8;
uniform sampler2D shadowMap;
uniform sampler2D reflection;
uniform float Texelation;
uniform mat4 WVM;
uniform mat4 Model;
uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform Material Brick;
uniform Material Water;
uniform Material Grass;
uniform float time;
//uniform sampler2D Texture1;
//varying vec3 varColor;
out vec4 color;
//varying in vec3 a; 
//varying vec3 varNormalf;
vec3 CalcNormal()
{
	vec3 Normal = normalize(fs_in.Normals);
	return Normal;
}
float ShadowCalculation(vec3 FragPos,vec3 lightDir, vec3 normal)
{
    // perform perspective divide
    vec3 projCoords = FragPos;
    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
	//if (projCoords.x > 1 || projCoords.y > 1)
	//	discard;
	projCoords.x = clamp(projCoords.x, 0.0 , 1.0);
	projCoords.y = clamp(projCoords.y, 0.0 , 1.0);
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // Get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
	float bias =  max(0.0005 * (1.0 - dot(normal, lightDir)), 0.00005);
    // Check whether current frag pos is in shadow
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

    return shadow;
}  


vec3 CalcBumpedNormal(vec4 normalTexture)
{
	vec3 Normal = CalcNormal();
	vec3 T = fs_in.T;
	T = normalize(T - dot(T, Normal) * Normal);
	vec3 B = cross(T, Normal);
//	B = fs_in.B;

	vec4 TexturedNormal = normalTexture;
	TexturedNormal = (TexturedNormal*2.0 - vec4(1.0));
	vec3 BumpMapNormal = vec3(TexturedNormal.xyz);// vec3(TexturedNormal.x, TexturedNormal.z, TexturedNormal.y);

	vec3 NewNormal;
	//mat3 TBN = mat3(vec3(1, 0, 0), vec3(0, 0, 1), Normal);
	mat3 TBN = mat3(T, B, Normal);
	NewNormal = TBN * BumpMapNormal;
	//NewNormal.x *= -1.0;
	//NewNormal.z *= -1.0;
	NewNormal = normalize(NewNormal);
	return NewNormal;
}
vec3 AddLight(Material material,vec3 LightColor, vec3 LightDir, vec4 normalTexture )
{
	// Mathematics
	vec3 toCameraVector = normalize(fs_in.FragPos - cameraPos);

	// Light
	vec3 ambient = LightColor * material.ambient;
	vec3 norm = CalcBumpedNormal(normalTexture);
	vec3 textnorm = normalize(norm);
	float diff = max(dot(textnorm, LightDir), 0.0);
	vec3 diffuse = diff * material.diffuse * LightColor;

	//  specular
	////vec3 reflectedLight = reflect(normalize(lightDir), norm);//phong
	vec3 reflectedLight = normalize(LightDir - normalize(toCameraVector));//blinn-phong
	////float spec = pow(max(dot(normalize(toCameraVector.xz), reflectedLight.xz), 0.0), shineDamper);//phong
	float spec = pow(max(dot(norm, reflectedLight), 0.0), int(material.diffuse * 128.0));//blinn-phong
	vec3 specular = material.specular * spec * LightColor;
	float shadow = ShadowCalculation(fs_in.LightFragPos,LightDir, textnorm);       
	vec3 Light = (diffuse + ( 1.0 * specular + ambient));
	return Light;
}
vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{ 
	float height_scale = 1;
    float height =  texture(Texture4, texCoords).r;    
    vec2 p = viewDir.xy / viewDir.z * (height * height_scale);
    return texCoords - p;    
} 
void main()
{
	float WaveOffset = time/500000.0f;
	float waveStrength = 0.5f;
	vec2 ndc = (fs_in.clipSpace.xy / fs_in.clipSpace.w) / 2.0 + 0.5;
	vec2 refractTexCoords = ndc;
	vec2 reflectTexCoords = ndc;

	//vec3 lightDir = normalize(lightPos - fs_in.FragPos);
	//vec3 toCameraVector = normalize(fs_in.FragPos - cameraPos);

	// distortion
	vec2 distortionTexCoords = texture(Texture0, (fs_in.UVs + vec2(WaveOffset, 0.0)) * Texelation).rg * 0.1; 
	distortionTexCoords = fs_in.UVs + vec2(distortionTexCoords.x,distortionTexCoords.x + WaveOffset);
	vec2 dudvmap = (texture(Texture0,distortionTexCoords * Texelation).rg * 2.0 - 1.0) * waveStrength;

	reflectTexCoords += dudvmap;
	reflectTexCoords = clamp(reflectTexCoords,0.001,0.999);
	reflectTexCoords *= vec2(1,-1);
	//vec2 TextureCoords = ParallaxMapping(fs_in.UVs, toCameraVector) * Texelation;
	vec4 color0 = texture2D(Texture0, fs_in.UVs * Texelation);
	vec4 color1 = texture2D(Texture1, (fs_in.UVs + vec2(time/500000.0f)) * Texelation);


	//vec3 LightColor = vec3(1,0.9,0.7);
	//vec3 WaterColor = vec3(0,0.3,0.7);


	////// Grass Bumped
	//vec3 WaterLight = AddLight(Grass, LightColor, lightDir, color1);
	//vec3 TotalWaterColor = WaterLight * WaterColor;

	//vec3 TotalColor = TotalWaterColor;
	//vec3 grey = vec3(0.5,0.5,0.5);
	//color = vec4(TotalWaterColor,1);
	//color = texture(reflection,reflectTexCoords);
	
	vec3 LightColor = vec3(1.0,0.9,0.7);
	vec3 lightDir = normalize(lightPos - fs_in.FragPos);
	vec3 toCameraVector = normalize(fs_in.FragPos - cameraPos);
	vec3 LightColorCalculated = AddLight(Water,LightColor,lightDir,texture2D(Texture1,dudvmap/* + vec2(time/200000.0) )* Texelation*/));

	vec4 reflectionColor = texture(Texture3,reflectTexCoords);

	vec4 pureWaterColor = vec4(LightColorCalculated, 1.0f);
	color = mix(reflectionColor,pureWaterColor,0.7);
	//color = reflectionColor;//vec4(1.0) * texture2D(Texture1,fs_in.UVs * 10.0);//* vec4(LightColorCalculated,1.0);// * LightColor;
//color = vec4(1);

}

