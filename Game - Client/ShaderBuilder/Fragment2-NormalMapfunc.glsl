vec3 CalcNormal(sampler2D normalTexture)
{
	vec3 Normal =  normalize(fs_in.Normals);
	vec3 T = fs_in.T;
	T = normalize(T - dot(T, Normal) * Normal);
	vec3 B = cross(T, Normal);
	B = fs_in.B;
	
	vec4 TexturedNormal = texture2D(normalTexture, fs_in.UVs);
	
	
	TexturedNormal = TexturedNormal*2.0 - vec4(1.0);
	
	vec3 BumpMapNormal = vec3(TexturedNormal.xyz);// vec3(TexturedNormal.x, TexturedNormal.z, TexturedNormal.y);

	vec3 NewNormal;
	mat3 TBN = mat3(T, B, Normal);
	NewNormal = TBN * BumpMapNormal;

	NewNormal = normalize(NewNormal);
//NewNormal = pow(NewNormal ,vec3(1.0f));
//return TexturedNormal ;
	float factor = 1.0f;	
	NewNormal = NewNormal * (1.0-factor)  + Normal  * factor;
	return NewNormal;
}