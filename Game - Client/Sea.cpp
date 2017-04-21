#include "Sea.h"



Sea::Sea()
{
}


Sea::~Sea()
{
}

void Sea::Draw(mat4 & ProjectionMat, mat4 & ViewMat, mat4 & ModelMat)
{
	static float WaveOffset = 0.0f;
	WaveOffset += 0.0001f * Camera::Delta;
	if (WaveOffset > 2.0f)
	{
		WaveOffset -= 2.0f;
	}
	Camera& camera = Camera::GetCamera("Main");

	vec3 CameraPosition = camera.GetCameraPosition();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ViewportTexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, ReflectionTexture);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, DUDVtexture);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, ViewportRBO);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, NormalMap);


	shader.Use();
	glUniform1i(glGetUniformLocation(shader.ProgramID, "ViewportTexture"), 0); 
	glUniform1i(glGetUniformLocation(shader.ProgramID, "ReflectionTexture"), 1);
	glUniform1i(glGetUniformLocation(shader.ProgramID, "DUDVmap"), 2);
	glUniform1i(glGetUniformLocation(shader.ProgramID, "DepthMap"), 3);
	glUniform1i(glGetUniformLocation(shader.ProgramID, "NormalMap"), 4);
	glUniform1f(glGetUniformLocation(shader.ProgramID, "WaveOffset"), WaveOffset);
	glUniform3fv(glGetUniformLocation(shader.ProgramID, "cameraPosition"), 1, value_ptr(CameraPosition));
	glUniform3fv(glGetUniformLocation(shader.ProgramID, "LightPos"), 1, value_ptr(vec3(100,100.0,0)));
	glUniformMatrix4fv(glGetUniformLocation(shader.ProgramID, "projectionMat"), 1, GL_FALSE, value_ptr(ProjectionMat));
	glUniformMatrix4fv(glGetUniformLocation(shader.ProgramID, "viewMat"), 1, GL_FALSE, value_ptr(ViewMat));
	glUniformMatrix4fv(glGetUniformLocation(shader.ProgramID, "modelMat"), 1, GL_FALSE, value_ptr(ModelMat));



	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, Vertices_Amount);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}
void Sea::Initialize()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glGenFramebuffers(1, &ViewportFBO);
	glGenFramebuffers(1, &ReflectionFBO);
	Mouse& mouse = Mouse::Instanace();

	// Viewport Texture
	glGenTextures(1, &ViewportTexture);
	glBindTexture(GL_TEXTURE_2D, ViewportTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindFramebuffer(GL_FRAMEBUFFER, ViewportFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ViewportTexture, 0);

	glGenTextures(1, &ViewportRBO);
	glBindTexture(GL_TEXTURE_2D, ViewportRBO);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindFramebuffer(GL_FRAMEBUFFER, ViewportFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, ViewportRBO, 0);

	//glGenRenderbuffers(1, &ViewportRBO);
	//glBindRenderbuffer(GL_RENDERBUFFER, ViewportRBO);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y);
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, ViewportRBO);
	//glBindTexture(GL_TEXTURE_2D, 0);
	// Reflection Texture
	glGenTextures(1, &ReflectionTexture);
	glBindTexture(GL_TEXTURE_2D, ReflectionTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindFramebuffer(GL_FRAMEBUFFER, ReflectionFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ReflectionTexture, 0);

	glGenRenderbuffers(1, &ReflectionRBO);
	glBindRenderbuffer(GL_RENDERBUFFER, ReflectionRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, ReflectionRBO);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Load DUDV map
	/// texture
	glGenTextures(1, &DUDVtexture);
	glBindTexture(GL_TEXTURE_2D, DUDVtexture);
	/// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	/// Load, create texture and generate mipmaps
	{
		int width, height;
		unsigned char* image = SOIL_load_image("Map/waterDUDV.png", &width, &height, 0, SOIL_LOAD_AUTO);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		if (image)
		SOIL_free_image_data(image);
	}

	glEnable(GL_TEXTURE_2D);
	//unbind texture 2d
	glBindTexture(GL_TEXTURE_2D, 0);

	// Load Normal map
	/// texture
	glGenTextures(1, &NormalMap);
	glBindTexture(GL_TEXTURE_2D, NormalMap);
	/// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	/// Load, create texture and generate mipmaps
	
	{
		int width, height;
		unsigned char* image = SOIL_load_image("Map/waterNormal.png", &width, &height, 0, SOIL_LOAD_AUTO);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		if (image)
		SOIL_free_image_data(image);
	}
	glEnable(GL_TEXTURE_2D);


	//unbind texture 2d
	glBindTexture(GL_TEXTURE_2D, 0);


	// Load others
	Load_VAO();
	Load_Shader();
	Load_World_Shaders();
	InitializeRefraction();
	InitializeReflection();
}
void Sea::Load_Shader()
{
	shader = *(new Shader("Sea Vertex Shader.glsl","Sea Geometry Shader.glsl", "Sea Fragment Shader.glsl"));
}
void Sea::Load_VAO()
{
	vertices.push_back(Vertices{ vec3(-1, 0, -1) , vec2(0,0) });
	vertices.push_back(Vertices{ vec3(1, 0, -1) , vec2(1,0) });
	vertices.push_back(Vertices{ vec3(-1, 0, 1) , vec2(0,1) });
						  
	vertices.push_back(Vertices{ vec3(1, 0, 1) , vec2(1,1) });
	vertices.push_back(Vertices{ vec3(1, 0, -1) , vec2(1,0) });
	vertices.push_back(Vertices{ vec3(-1, 0, 1) , vec2(0,1) });



	// generate buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind arrays
	glBindVertexArray(VAO);
	// bind vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertices), &vertices.front(), GL_STATIC_DRAW);

	// vertices
	/// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertices), BUFFER_OFFSET(sizeof(vec3)));
	glEnableVertexAttribArray(1);

	// Unbind VAO
	glBindVertexArray(0);

	// free memory
	Vertices_Amount = vertices.size() * 3;
	vertices.clear();
}
void Sea::Load_World_Shaders()
{ 
	sReflection_Ground = Shader("Sea-Ground reflection Vertex Shader.glsl", "Sea-Ground reflection Fragment Shader.glsl");
	sRefraction_Ground = Shader("Sea-Ground refraction Vertex Shader.glsl", "Sea-Ground refraction Fragment Shader.glsl");
	sUnit = Shader("Sea-Unit Vertex Shader.glsl", "Sea-Unit Fragment Shader.glsl");
}
void Sea::InitializeRefraction()
{
	Mouse& mouse = Mouse::Instanace();
	glBindFramebuffer(GL_FRAMEBUFFER, ViewportFBO);
	GLuint test = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	glViewport(0, 0, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y);

	//glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
void Sea::InitializeReflection()
{
	Mouse& mouse = Mouse::Instanace();

	glBindFramebuffer(GL_FRAMEBUFFER, ReflectionFBO);
	GLuint test = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	glViewport(0, 0, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y);

	//glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// | GL_STENCIL_BUFFER_BIT);
}
void Sea::BindRefraction()
{
	glBindFramebuffer(GL_FRAMEBUFFER, ViewportFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
void Sea::BindReflection()
{
	glBindFramebuffer(GL_FRAMEBUFFER, ReflectionFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// | GL_STENCIL_BUFFER_BIT);
}