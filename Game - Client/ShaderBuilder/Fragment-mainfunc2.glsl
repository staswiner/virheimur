	float near = 10.0f;
	float far = 200.0f;
	float depth = gl_FragCoord.z;
	//float Distance = (2.0 * near * far) / (far + near - (2.0 * depth - 1.0) * (far - near));
	float cameraToFragDist = distance(fs_in.FragPos, cameraPos);
	float Distance = (2*near + far - cameraToFragDist) /(near+far);	
	
	if (Distance > 1.0f) Distance = 1.0f;
	if (Distance < 0.0f) Distance = 0.0f;
	Distance  = pow(Distance,1.0);

	color = vec4(TotalColor, 1);
	float gamma = 1.0;
	color.rgb = pow(color.rgb, vec3(1.0/gamma));

	color.rgb = vec3(Distance) * color.rgb + vec3(1.0-Distance) * vec3(0.7, 0.7, 1.0) ;
	//color.rgb = CalcNormal(NormalMap[0]);
}