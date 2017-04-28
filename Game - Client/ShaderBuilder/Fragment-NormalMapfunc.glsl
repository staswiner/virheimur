vec3 CalcBumpedNormal(sampler2D normalTexture)
		{
		vec3 Normal = CalcNormal();
		vec3 T = fs_in.T;
		T = normalize(T - dot(T, Normal) * Normal);
		vec3 B = cross(T, Normal);
		//B = fs_in.B;

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
		return NewNormal;
		}