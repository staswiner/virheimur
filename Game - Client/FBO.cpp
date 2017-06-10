#include "FBO.h"



FBO::FBO()
{
}



FBO::~FBO()
{
	//glDeleteFramebuffers(1,&PostProcessingFBO);
	//glDeleteRenderbuffers(1,&RBO);

}

bool FBO::Initialize(float Width, float Height, Shader* shader)
{
	// todo: make the buffer size maximum or dynamic
	Mouse& mouse = Mouse::Instanace();
	this->Width = mouse.GetWindowSize().x / Width;
	this->Height = mouse.GetWindowSize().y / Height;
	glGenFramebuffers(1, &ID);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->Width,
		this->Height, 0, GL_RGB, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindFramebuffer(GL_FRAMEBUFFER, ID);
	
	GLuint test = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
	// render buffer object

	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 
		this->Width,
		this->Height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	Load_Interface(shader);


	glBindFramebuffer(GL_FRAMEBUFFER, ID);
	test = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	glViewport(0, 0, this->Width,
		this->Height);

	glClearColor(0, 0, 0, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return true;
	}
	else
	return false;

}
bool FBO::InitializeBig(int Height, int Width, Shader* shader)
{
	// todo: make the buffer size maximum or dynamic
	Mouse& mouse = Mouse::Instanace();
	this->Width = mouse.GetWindowSize().x / Width;
	this->Height = mouse.GetWindowSize().y / Height;
	glGenFramebuffers(1, &ID);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, this->Width,
		this->Height, 0, GL_RGB, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindFramebuffer(GL_FRAMEBUFFER, ID);

	GLuint test = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
	// render buffer object

	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8,
		this->Width,
		this->Height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	Load_Interface(shader);

	//	 Mouse& mouse = Mouse::Instanace();
	glBindFramebuffer(GL_FRAMEBUFFER, ID);
	test = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	glViewport(0, 0, this->Width,
		this->Height);

	glClearColor(0, 0, 0, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return true;
	}
	else
		return false;

}
void FBO::BindFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, ID);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	glEnable(GL_CLIP_DISTANCE0);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glClearColor(255,255,255,255);
	glDepthMask(GL_TRUE);
	glViewport(0, 0, this->Width,this->Height);
}
void FBO::UnbindFrameBuffer()
{
	Mouse& mouse = Mouse::Instanace();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, mouse.GetWindowSize().x, mouse.GetWindowSize().y);
}
void FBO::DrawFrameBuffer()
{
	Draw_Interface();
}
void FBO::DrawFrameBuffer(int Top, int Left, int Width, int Height)
{
	Draw_Interface();
}
void FBO::ChangeBuffersSize()
{
	Mouse& mouse = Mouse::Instanace();

	if (ID == 0)
		return;
	glBindFramebuffer(GL_FRAMEBUFFER, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y, 0, GL_RGB, GL_FLOAT, NULL);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void FBO::Resize(float Width, float Height)
{
	if (ID == 0)
		return;
	glBindFramebuffer(GL_FRAMEBUFFER, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)Width, (int)Height, 0, GL_RGB, GL_FLOAT, NULL);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, (int)Width, (int)Height);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

vec4 FBO::GetPixel(int x, int y)
{
	glBindFramebuffer(GL_FRAMEBUFFER, this->ID);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	vec4 pixel;
	glReadPixels(x , y, 1, 1, GL_RGBA, GL_FLOAT, &pixel);
	FBO::UnbindFrameBuffer();
	return pixel;
}

void FBO::Load_VAO()
{
	pair<float,float> xEdge = { 1,0 };
	pair<float,float> yEdge = { 0,-1 };
	vertices.push_back(Vertices(vec2(xEdge.second, yEdge.second), vec2(0, 0) ));//|34-|
	vertices.push_back(Vertices(vec2(xEdge.first, yEdge.second),vec2(1, 0)	 ));	//|12-|
	vertices.push_back(Vertices(vec2(xEdge.second, yEdge.first),vec2(0, 1)	 ));	//|---|

	vertices.push_back(Vertices(vec2(xEdge.first, yEdge.first), vec2(1, 1)	));
	vertices.push_back(Vertices(vec2(xEdge.first, yEdge.second), vec2(1, 0) )); // 2
	vertices.push_back(Vertices(vec2(xEdge.second, yEdge.first),vec2(0, 1)	)); // 3

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
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertices), (char*)NULL);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertices), (const void*)(NULL+sizeof(vec2)));
	glEnableVertexAttribArray(1);

	// Unbind VAO
	glBindVertexArray(0);

	// free memory
	Vertices_Amount = vertices.size() * 3;
	vertices.clear();
}
void FBO::Draw_Interface()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	shader->Use();
	GLint test = glGetUniformLocation(shader->ProgramID, "ourTexture");
	glUniform1i(test, 0);

	GL::DrawTriangles(VAO, Vertices_Amount);
}
void FBO::DrawMultipleTextures(vector<GLuint> textures,vector<string> ShaderNames)
{
	for (size_t i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0+i);
		glBindTexture(GL_TEXTURE_2D, textures[i]);
	}
	glActiveTexture(GL_TEXTURE0);
	shader->Use();
	for (size_t i = 0; i < textures.size(); i++)
	{
		GLint test = glGetUniformLocation(shader->ProgramID, ShaderNames[i].c_str());
		glUniform1i(test, i);
	}
	// Draw
	GL::DrawTriangles(VAO, Vertices_Amount);
}
void FBO::Load_Interface(Shader* shader)
{
	Load_VAO();
	this->shader = shader;
}