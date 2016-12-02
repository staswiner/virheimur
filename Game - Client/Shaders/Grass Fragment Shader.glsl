#version 400 core
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;


out vec4 color;

uniform sampler2D ourTexture;
uniform float AmbientStrength;
uniform vec3 lightPos;
uniform vec3 cameraPos;


void main()
{
	float specularStrength = 0.5f;
	
	vec4 texColor = texture(ourTexture, TexCoords);
	vec3 ambient = AmbientStrength * vec3(1,1,1);
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(1,1,1);
	
	vec3 viewDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * vec3(1,1,1);  

	vec3 result = (ambient + diffuse + specular) * vec3(texColor.x, texColor.y, texColor.z);
	color = vec4(result, 1.0f);
}