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
uniform sampler2D Texture3;//road texture
uniform sampler2D Texture4;//road normal texture
uniform sampler2D Texture5;//road bump texture
uniform sampler2D Texture6;//road dark texture
uniform sampler2D Texture7;//texture normal texture
uniform sampler2D Texture8;
uniform sampler2D shadowMap;
uniform float Texelation;
uniform mat4 WVM;
uniform mat4 Model;
uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform Material Brick;
uniform Material Water;
uniform Material Grass;
//uniform sampler2D Texture1;
//varying vec3 varColor;
out vec4 color;
//varying in vec3 a; 
//varying vec3 varNormalf;

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

vec3 CalcNormal()
{
	vec3 Normal = normalize(fs_in.Normals);
	return Normal;
}
vec3 CalcBumpedNormal(sampler2D normalTexture)
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
vec3 AddLight(Material material,vec3 LightColor, vec3 LightDir, sampler2D normalTexture)
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
	shadow = 0;   
	vec3 Light = (diffuse + (1.0 - shadow) * ( 4.0 * specular + ambient));
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
	
	vec3 lightDir = normalize(lightPos - fs_in.FragPos);
	vec3 toCameraVector = normalize(fs_in.FragPos - cameraPos);
	vec2 TextureCoords = ParallaxMapping(fs_in.UVs, toCameraVector) * Texelation;
	vec4 color0 = texture2D(Texture0, fs_in.UVs * Texelation);
	vec4 color1 = texture2D(Texture1, fs_in.UVs * Texelation);
	vec4 color2 = texture2D(Texture2, fs_in.UVs);
	vec4 color3 = texture2D(Texture3, fs_in.UVs * Texelation);
	vec4 color5 = texture2D(Texture5, fs_in.UVs * Texelation);
	vec4 color6 = texture2D(Texture6, fs_in.UVs * Texelation);
	vec4 color8 = texture2D(Texture8, fs_in.UVs * Texelation);
	vec3 LightColor = vec3(1,0.9,0.7);
	vec3 WaterColor = vec3(0,0.3,0.7);
	// first light component
	float ambientStrength = 0.1f;
	float diffuseStrength = 0.5f;
	float specularStrength = 0.5f;
	Material brickMaterial;
	brickMaterial.ambient = vec3(0.25);
	brickMaterial.diffuse = vec3(0.4f);
	brickMaterial.specular = vec3(0.774597);
	brickMaterial.shininess = 0.6f;


	// flat Light
	vec3 norm = CalcNormal();//CalcBumpedNormal(); (0,1,0)
	vec3 normal = normalize(norm); // (0,1,0)
	float diff = max(dot(normal, lightDir), 0.0); // (0,1,0)*(0,0,0) - (0.35,0.65,0) = -0.65 
	vec3 diffuse = diff * diffuseStrength * LightColor;

	//// flat specular
	float shineDamper = 16;
	
	//vec3 reflectedLight = normalize(reflect(lightDir, norm));
	vec3 reflectedLight= normalize(lightDir - normalize(toCameraVector));//blinn-phong
	//float spec = pow(max(dot(v1, v2) * 1.5, 0.0),shineDamper);
	float spec = pow(max(dot(norm, reflectedLight), 0.0), shineDamper);//blinn-phong

	vec3 specular = specularStrength * spec * LightColor;
	vec3 FlatLight = (diffuse + specular);

	/// Brick
	// bumped Light
	vec3 BrickLight = AddLight(Brick, LightColor, lightDir, Texture4);
	vec3 BrickColor = vec3(color6) * BrickLight * vec3(color3);

	float waterDepth = color5.g; // calculation optimization
	float lightPower = FlatLight.r;
	vec3 Water = (1.0- lightPower) * FlatLight * WaterColor + (lightPower) * FlatLight * LightColor;

	vec3 TotalTileColor = BrickColor * (1.0 - waterDepth) + Water * (waterDepth);

	// Grass Bumped
	vec3 GrassLight = AddLight(Grass, LightColor, lightDir, Texture7);
	vec3 GrassColor = vec3(color0) * GrassLight * vec3(color8);

	//vec4 WaterLayer = (waterDepth) * 
	//	((vec4(LightColor, 1.0) * LightStrength)
	//	+ (vec4(WaterColor, 1.0) * (1.0-LightStrength)));// +vec4(WaterColor, 1.0);

	//vec4 TextureLayer = color3 * (1 - waterDepth) * vec4(LightColor, 1.0) * LightStrengthBumped;
	////color = (color3 * vec4(diffuseBumped, 1.0) * color5) * color2.r * DistanceLightFade;
	//color = (TextureLayer + WaterLayer);
	//color = TextureLayer;
	vec3 TotalColor = GrassColor * color2.r + TotalTileColor * (1.0f - color2.r);
	color = vec4(TotalColor,1);
	//float DistanceLightFade = min(1.0,10.0f/sqrt(distance(fs_in.FragPos, lightPos)));
	//color5 = color5 * 2 - vec4(1);
	//color5 = vec4(1);
	//if (color2.r < 0.5)
	//// normal version
	//if (abs(dot(norm, vec3(0, 1, 0))) > 0.8)
	//{
	//	color = (color3 * vec4(diffuseBumped, 1.0) * color5) * DistanceLightFade;// *vec4(TexturedNormal.z, TexturedNormal.z, TexturedNormal.z, 1);
	//}
	//else
	//{
	//	color = ((color0 * dot(norm, vec3(0.0, 1.0, 0.0)) * vec4(diffuse, 1.0f)) +
	//			(color1 * (1.0 - dot(norm, vec3(0.0, 1.0, 0.0)))) * vec4(diffuse, 1.0f)) * DistanceLightFade;
	//}
	// Tiled version
	//color = (color3 * vec4(diffuseBumped, 1.0) * color5) * color2.r * DistanceLightFade/* +
	//	((color0 * dot(norm, vec3(0.0, 1.0, 0.0)) * vec4(diffuse, 1.0f)) + 
	//	(color1 * (1.0 - dot(norm, vec3(0.0, 1.0, 0.0)))) * vec4(diffuse, 1.0f)) * (1.0-color2.r) * DistanceLightFade*/;


}

