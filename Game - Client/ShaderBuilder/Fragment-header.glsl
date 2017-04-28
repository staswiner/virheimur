#version 400 compatibility
			in GS_OUT{
			vec2 UVs;
			vec3 Normals;
			vec3 FragPos;
			vec4 clipSpace;
			vec3 LightFragPos;
			vec3 T;
			vec3 B;
			}fs_in;
			struct Material {
				vec3 ambient;
				vec3 diffuse;
				vec3 specular;
				vec3 emissive;
				float shininess;
			};
			uniform sampler2D Texture[5];
			uniform sampler2D NormalMap[5];
			uniform sampler2D Dispose;
			uniform vec3 lightPos;
			uniform vec3 cameraPos;
			uniform Material material;
			out vec4 color;