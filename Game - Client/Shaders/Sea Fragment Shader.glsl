#version 400 core
in vec2 TexCoords;
in vec4 clipSpace;
in vec3 toCameraVector;
in vec3 fromLightVector;
in vec3 WorldPos;

out vec4 color;



uniform sampler2D ViewportTexture;
uniform sampler2D ReflectionTexture;
uniform sampler2D DUDVmap;
uniform sampler2D DepthMap;
uniform sampler2D NormalMap;

uniform vec3 cameraPosition;


uniform float WaveOffset;
const float waveStrength = 0.4f;
const float shineDamper = 20.0f;
const float reflectivity = 0.5f;
const vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
void main()
{
	vec2 ndc = (clipSpace.xy / clipSpace.w) / 2.0 + 0.5;
	vec2 refractTexCoords = vec2(ndc.x, ndc.y);
	vec2 reflectTexCoords = vec2(ndc.x, -ndc.y);

	// depth
	float near = 0.1f;
	float far = 1000.0f;
	float depth = texture(DepthMap, refractTexCoords).y;
	float floorDistance = 2.0 * near * far / (far + near - ( 2.0 * depth - 1.0 ) * (far - near));
	depth = gl_FragCoord.z;
	float waterDistance = 2.0 * near * far / (far + near - ( 2.0 * depth - 1.0 ) * (far - near));
	float waterDepth = floorDistance - waterDistance;

	// distortion
	vec2 distortionTexCoords = texture(DUDVmap, TexCoords + vec2(WaveOffset, 0.0)).rg * 0.1; 
	distortionTexCoords = TexCoords + vec2(distortionTexCoords.x,distortionTexCoords.x + WaveOffset);
	vec2 dudvmap = (texture(DUDVmap,distortionTexCoords).rg * 2.0 - 1.0) * waveStrength;

	// light
	vec4 Normals = texture(NormalMap,distortionTexCoords);
	//Normals = DUDVcolor;
	vec3 normal = vec3(Normals.r * 2.0 - 1.0,Normals.g * 2.0 - 1.0 ,Normals.b * 2.0 - 1.0); // change .b
	normal = normalize(normal); 

	vec3 reflectedLight = reflect(normalize(fromLightVector), normal);
	float specular = max(dot(reflectedLight, normalize(toCameraVector)), 0.0);
	specular = pow(specular, shineDamper);
	vec3 specularHighlights = lightColor * specular * reflectivity;




	refractTexCoords = clamp(refractTexCoords, 0.01, 0.99);
//	reflectTexCoords += distortionTexCoords;
	reflectTexCoords.x = clamp(reflectTexCoords.x, 0.001, 0.999);
	reflectTexCoords.y = clamp(reflectTexCoords.y, -0.999, -0.001);

	vec4 refractionColor = texture(ViewportTexture, refractTexCoords);
	vec3 reflectionColorSum = vec3(0,0,0);
	int Blur = 1;
	for(int x = -Blur; x <= Blur; x++)
	{
		for(int y = -Blur; y <= Blur; y++)
		{
			reflectionColorSum += vec3(texture(ReflectionTexture, reflectTexCoords + vec2(x,y) + ((dudvmap / 20.0) * clamp(waterDepth / 500.0, 0.0, 1.0)))) + specularHighlights;
		}
	}
	vec3 reflectionColorAverage = reflectionColorSum / ((Blur * 2.0 + 1.0 ) * (Blur * 2.0 + 1.0 ));
	vec4 reflectionColor = vec4(reflectionColorAverage, 1.0);


	vec3 viewVector = normalize(toCameraVector);
	float reflactiveFactor = dot(vec3(0.0, -1.0, 0.0) , viewVector);
	refractionColor = mix(refractionColor, vec4(0.0,0.5,0.5, 1.0), 0.5);
	color = mix(reflectionColor, refractionColor, reflactiveFactor);
	color = mix(color, vec4(0.4, 0.4, 0.8, 0.7), 0.3);
	color.a = clamp(waterDepth/5.0, 0.0, 1.0);
	//color = mix(vec4(0.0, 0.0, 1.0 - (waterDepth / 500.0f), 1.0), color, 0.5);
	//color = vec4(vec3(1.0 - waterDepth / 300.0f), 1.0f);
	//color = Normals;


	// variables : cameraPos, WorldPos
	float MaxVisibleDistance = 1000.0f;
	float DistanceToPixel = (MaxVisibleDistance - distance(-cameraPosition,WorldPos))/MaxVisibleDistance;
	DistanceToPixel = clamp(DistanceToPixel,0.0,1.0);
	vec3 FragColor3 = (vec3(color) * DistanceToPixel) + (vec3(1.0,1.0,1.0) * (1.0 - DistanceToPixel));
	color = vec4(FragColor3, 1.0f);

}