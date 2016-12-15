#version 400 core

layout(origin_upper_left) in vec4 gl_FragCoord;

in GS_OUT{
	float instanceID;
	float vertexID;
	float Height;
	float index;
	vec3 Normals;
	vec3 FragPos;
	vec4 UV;
} gs_out;
//in vec2 UVs;

//uniform sampler2D myTexture0;
uniform sampler2D Fractal;
uniform sampler2D CoverPicture;
uniform vec2 mousePos;
out vec4 color;


void main()
{
//{   // all syntax correct
	vec3 lightPos = vec3(30, 30, 0);
	vec3 norm = normalize(gs_out.Normals);
	vec3 lightDir = normalize(lightPos - gs_out.FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(0.6) + vec3(0.4);
//	//color = texture(myTexture0, UVs);
//	//if (isInstanced==true)
//	//{
//	//	//color = vec4(1, 1, 1, 1);
//	//}
//	/*if (Height < -10)
//		discard;*/
	vec3 result = diffuse * vec3(0.5, 0.6, 0);
	float vertexb2=mod(gs_out.instanceID,8);
	//color = vec4(0, (100.0 + vertexb2*4.0 + gs_out.vertexID*5.0) / 255.0, (10.0 + vertexb2 + gs_out.vertexID*5.0) / 255.0, 1);
	vec4 Image = texture(CoverPicture, (gs_out.UV.xz+vec2(100.0,100.0))/200.0f);

	color = vec4(vec3(0.25, 0.25 + (mod(gs_out.instanceID, 8)) / 255, 0) * diffuse, 1.0)*vec4(0.5+(gs_out.index/3.0));
	//color = texture(Fractal, gs_out.UV.xz/200.0f) * vec4(diffuse,1);
	float alpha = 1.0;
	if (distance(gl_FragCoord.xy, mousePos+vec2(8,8)) < 80)
		alpha = 0.5;
	color = Image * vec4(diffuse, alpha);
//	color = vec4(1);
}

  