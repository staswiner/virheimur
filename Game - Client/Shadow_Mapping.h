#pragma once
#include "Models_Header.h"
#include "FBO.h"
#include "Mouse.h"
class Shadow_Mapping
{
public:
	Shadow_Mapping();
	~Shadow_Mapping();
	void BindFrameBuffer();
	void Draw();
	Shader shader;
	GLuint depthMap;
private:
	void GenBuffers();
	void GenVAO();

	vector<vec2> vertices;
	GLuint VAO, VBO;
	GLuint Vertices_Amount;
	const GLuint ci_ShadowWidth = 1024, ci_ShadowHeight = 1024;
	GLuint depthMap_Framebuffer;
};

