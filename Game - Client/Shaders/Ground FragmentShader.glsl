#version 400 core
//in vec3 ourColor;
in vec4 gl_FragCoord;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 FragPosLightSpace;
in vec3 WorldPos;

out vec4 FragColor;

uniform sampler2D GrassTexture;
uniform sampler2D MountainTexture;
uniform sampler2D shadowMap;

uniform float AmbientStrength;
uniform vec3 lightPos;
uniform vec3 cameraPos;
//
float ShadowCalculation(vec4 fragPosLightSpace, float multiplier)
{
    float bias = 0.001;
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
   
    projCoords = projCoords * 0.5 + 0.5;
	if (projCoords.x > 1 || projCoords.y > 1 || projCoords.x < 0 || projCoords.y < 0)
		return 0.0f;
    float closestDepth = texture(shadowMap, projCoords.xy).z; 

    float currentDepth = projCoords.z;
	float shadow = 0.0f;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	for(int x = -1; x <= 1; x++)
	{
		for(int y = -1; y <= 1; y++)
		{
			float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
			shadow += currentDepth - bias > pcfDepth ? (1.0 * multiplier) : 0.0;
		}
	}
	shadow /= 9.0;
    return shadow;
	return 0;
}
void main()
{
	
	vec3 GrassColor = texture(GrassTexture, TexCoord).rgb;
	vec3 MountainColor = texture(MountainTexture, TexCoord).rgb;
	vec3 normal = normalize(Normal);
	vec3 lightColor = vec3(1.0,1.0,1.0);
	vec3 defaultColor = vec3(0.25);
	// Ambient
	vec3 ambient = AmbientStrength * defaultColor;
	// diffuse
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(lightDir, normal), 1.25);
	vec3 diffuse = diff * lightColor;
	// Specular
	vec3 viewDir = normalize(-cameraPos - FragPos);
	float spec = 0.1;
	vec3 halfwayDir = normalize(lightDir + viewDir);
	spec = pow(max(dot(normal, halfwayDir), 0.0), 2.0);
	vec3 specular = spec * lightColor; 
	// Calculate shadow
	vec3 distance = normalize(lightPos - FragPos);
	float shadowMultiplier = distance.y / 1.0f;
	shadowMultiplier = 1.0f;
	float shadow = ShadowCalculation(FragPosLightSpace, shadowMultiplier);
	vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));// *GrassColor;

	float TextureComponent = dot(normal, vec3(0, 1.0, 0));
	/*if (TextureComponent > 0.7)
		lighting *= GrassColor;
	else
		lighting *= MountainColor;*/
	lighting *= GrassColor * TextureComponent + MountainColor * (1.0 - TextureComponent);
	float MaxVisibleDistance = 1000.0f;
	float DistanceToPixel = (MaxVisibleDistance - distance(-cameraPos,WorldPos))/MaxVisibleDistance;
	DistanceToPixel = clamp(DistanceToPixel,0.0,1.0);
	vec3 FragColor3 = (lighting * DistanceToPixel) + (vec3(0.9,0.8,0.5) * (1.0 - DistanceToPixel));
	FragColor = vec4(FragColor3, 1.0f);
//	FragColor = vec4(1.0f);
}