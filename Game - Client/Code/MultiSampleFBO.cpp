#include "MultiSampleFBO.h"



MultiSampleFBO::MultiSampleFBO()
{
}


MultiSampleFBO::~MultiSampleFBO()
{
}

bool MultiSampleFBO::InitializeMultiSample()
{
	glGenFramebuffers(1, &PostProcessingFBO);

	glGenTextures(1, &texture);

	Mouse mouse; // todo: make the buffer size maximum or dynamic
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texture);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindFramebuffer(GL_FRAMEBUFFER, PostProcessingFBO);

	GLuint test = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, texture, 0);
	// render buffer object

	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	//	Mouse mouse;
	glBindFramebuffer(GL_FRAMEBUFFER, PostProcessingFBO);
	test = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	glViewport(0, 0, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y);

	glClearColor(0, 0, 0, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return true;
	}
	else
		return false;
}

void MultiSampleFBO::BindFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, PostProcessingFBO);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glClearColor(0.0f, 0.0f, 0, 0);
	//glDepthMask(GL_TRUE);

}
void MultiSampleFBO::ChangeBuffersSize()
{
	Mouse mouse;
	if (PostProcessingFBO == 0)
		return;
	glBindFramebuffer(GL_FRAMEBUFFER, PostProcessingFBO);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y, GL_TRUE);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, (int)mouse.GetWindowSize().x, (int)mouse.GetWindowSize().y);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void MultiSampleFBO::CopyBuffer(GLuint newFBO)
{
	Mouse mouse;
	GLuint width = mouse.GetWindowSize().x, height = mouse.GetWindowSize().y;
	glBindFramebuffer(GL_READ_FRAMEBUFFER, PostProcessingFBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, newFBO);
	glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

