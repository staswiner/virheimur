#version 400 core

in vec2 UVs;
in vec3 Normals;
in vec3 FragPos;
//flat in int InstanceID;
uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform float Texelation;
//uniform sampler2D Texture1;
//varying vec3 varColor;
out vec4 color;


void main()
{   
	vec3 lightPos = vec3(30,30,0);
	vec3 norm = normalize(Normals);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(1);

	////color = texture(myTexture0, UVs);
	////else
	////{
	//if (textureSize(Texture0).x > 0)
	{
		float near = 0.1f;
		float far = 1000.0f;
		float depth = gl_FragCoord.z;
		float Distance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));

		color = texture2D(Texture0, UVs * Texelation);// *vec4(diffuse, 1);
		//color = vec4(0,0.5,0.1,1.0) * vec4(diffuse, 1);

	}
	//else
	{
	//	vec3 result = diffuse * (vec3(255, 255, 240) / 255.0);
	//	color = vec4(result, 1.0);
	}
	//}
	//color = vec4(0.0,1.0,1.0,1.0);
}

  