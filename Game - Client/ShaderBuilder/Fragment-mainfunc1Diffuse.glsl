	vec4 color0 = texture2D(Texture[0], fs_in.UVs);
			vec3 TotalColor = vec3(color0) * AddLight(material, LightColor, lightDir