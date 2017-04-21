#include "Shadow_Mapping.h"



Shadow_Mapping::Shadow_Mapping()
{
	this->GenBuffers();
	shader = Shader("Shadow Vertex Shader.glsl", "Shadow Fragment Shader.glsl");
}


Shadow_Mapping::~Shadow_Mapping()
{
}

void Shadow_Mapping::BindFrameBuffer()
{
	Mouse& mouse = Mouse::Instanace();

	glViewport(0, 0, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y);
	//glViewport(0, 0, ci_ShadowWidth, ci_ShadowHeight);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMap_Framebuffer);
	int test = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void Shadow_Mapping::Draw()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	Shader::At("FBO").Use();
	//shader.Use();
	glUniform1i(glGetUniformLocation(Shader::At("FBO").ProgramID, "ourTexture"), 0);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, Vertices_Amount);
	glBindVertexArray(0);
}

void Shadow_Mapping::GenBuffers()
{
	Mouse& mouse = Mouse::Instanace();

	int width = (int)mouse.GetWindowSize().x;
	int height = (int)mouse.GetWindowSize().y;
	// generate a framebuffer to store the depth test values

	glGenFramebuffers(1, &depthMap_Framebuffer);

	// generate texture buffer of the shadow mapping
	
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// bind texture buffer to the shadow mapping frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMap_Framebuffer);
	GLuint test = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // bind to other frame buffer
	GenVAO();
}

void Shadow_Mapping::GenVAO()
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
