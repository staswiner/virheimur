vec3 textnorm = normalize(norm);
			float diff = max(dot(textnorm, LightDir), 0.0);
			vec3 diffuse = diff * material.diffuse * LightColor;

			//  specular
			////vec3 reflectedLight = reflect(normalize(lightDir), norm);//phong
			vec3 reflectedLight = normalize(LightDir - normalize(toCameraVector));//blinn-phong
			////float spec = pow(max(dot(normalize(toCameraVector.xz), reflectedLight.xz), 0.0), shineDamper);//phong
			float spec = pow(max(dot(norm, reflectedLight), 0.0), int(material.specular));//blinn-phong
			vec3 specular = spec * LightColor;
			//	float shadow = ShadowCalculation(fs_in.LightFragPos,LightDir, textnorm);    "
			// Enable Shadows
			//	shadow = 0;
			vec3 emissive = material.emissive;
			vec3 Light = (diffuse + (specular + ambient));
			return Light;
		}