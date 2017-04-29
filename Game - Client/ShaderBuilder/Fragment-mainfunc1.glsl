void main()
{
	vec3 LightColor = vec3(1.0, 0.9, 0.7);
	vec3 lightDir = normalize(lightPos - fs_in.FragPos);