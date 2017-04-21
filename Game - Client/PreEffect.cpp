#include "PreEffect.h"



PreEffect::PreEffect()
{
}


PreEffect::~PreEffect()
{
}

bool PreEffect::Initialize()
{
	glGenFramebuffers(1, &PreEffectFBO);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// todo: make the buffer size maximum or dynamic
	Mouse& mouse = Mouse::Instanace();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y, 0, GL_RGB, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindFramebuffer(GL_FRAMEBUFFER, PreEffectFBO);

	GLuint test = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
	// render buffer object

	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	Load_Interface();

	//	 Mouse& mouse = Mouse::Instanace();
	glBindFramebuffer(GL_FRAMEBUFFER, PreEffectFBO);
	test = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	glViewport(0, 0, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y);

	glClearColor(0, 0, 0, 0);

	return true;

}
void PreEffect::BindFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, PreEffectFBO);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glDepthMask(GL_TRUE);

}
void PreEffect::DrawFrameBuffer()
{
//	glBindFramebuffer(GL_FRAMEBUFFER, PostProcessingFBO);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// Mouse& mouse = Mouse::Instanace();
	//glViewport(0, 0, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y);
	Draw_Interface();

}
void PreEffect::ChangeBuffersSize()
{
	Mouse& mouse = Mouse::Instanace();

	if (PreEffectFBO == 0)
		return;
	glBindFramebuffer(GL_FRAMEBUFFER, PreEffectFBO);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y, 0, GL_RGB, GL_FLOAT, NULL);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void PreEffect::Load_VAO()
{
	vertices.push_back(vec2(-1, -1));
	vertices.push_back(vec2(1, -1));
	vertices.push_back(vec2(-1, 1));

	vertices.push_back(vec2(1, 1));
	vertices.push_back(vec2(1, -1));
	vertices.push_back(vec2(-1, 1));

	// generate buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind arrays
	glBindVertexArray(VAO);
	// bind vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), &vertices.front(), GL_STATIC_DRAW);

	// vertices
	/// Position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (char*)NULL);
	glEnableVertexAttribArray(0);

	// Unbind VAO
	glBindVertexArray(0);

	// free memory
	Vertices_Amount = vertices.size() * 3;
	vertices.clear();
}
void PreEffect::Draw_Interface()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	shader.Use();
	glUniform1i(glGetUniformLocation(shader.ProgramID, "ourTexture"), 0);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, Vertices_Amount);
	glBindVertexArray(0);

}

void PreEffect::Load_Interface()
{
	Load_VAO();
	shader = Shader("PostProcessing Vertex Shader.glsl", "PostProcessing Fragment Shader.glsl");
}