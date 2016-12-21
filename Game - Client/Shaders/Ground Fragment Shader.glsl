#version 400 core

in vec2 UVs;
in vec3 Normals;
in vec3 FragPos;
//flat in int InstanceID;
uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform sampler2D Texture2;
uniform sampler2D Texture3;
uniform float Texelation;
//uniform sampler2D Texture1;
//varying vec3 varColor;
out vec4 color;


void main()
{
	vec3 lightPos = vec3(30, 30, 0);
	vec3 norm = normalize(Normals);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(1);

	//if (textureSize(Texture0).x > 0)
	{
		float near = 0.1f;
		float far = 1000.0f;
		float depth = gl_FragCoord.z;
		float Distance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));
		vec4 color0 = texture2D(Texture0, UVs * Texelation);
		vec4 color1 = texture2D(Texture1, UVs * Texelation);
		vec4 color2 = texture2D(Texture2, UVs);
		vec4 color3 = texture2D(Texture3, UVs * Texelation);
		//if (color2.r < 0.5)
		if (abs(dot(norm, vec3(0, 1, 0))) > 0.8)
		{
			color = color3;
		}
		else
		{
			color = (color0 * dot(norm, vec3(0, 1, 0))) + (color1 * (1 - dot(norm, vec3(0, 1, 0)))) * vec4(diffuse, 1.0f);
		}


	}
	//else
	{
		//	vec3 result = diffuse * (vec3(255, 255, 240) / 255.0);
		//	color = vec4(result, 1.0);
	}
}

