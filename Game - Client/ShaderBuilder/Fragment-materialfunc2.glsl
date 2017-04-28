{
			// Mathematics
			vec3 toCameraVector = normalize(fs_in.FragPos - cameraPos);

			// Light
			vec3 ambient = LightColor * material.ambient;