	float near = 0.1f;
	float far = 1000.0f;
	float depth = gl_FragCoord.z;
	float Distance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));

	color = vec4(TotalColor, 1);
	float gamma = 1.2;
	color.rgb = pow(color.rgb, vec3(1.0/gamma));
	//color.rgb = CalcNormal(NormalMap[0]);
}