#pragma once
#include "Shader.h"
#include "ShaderBuilder.h"
#include "Graphics_Header.h"
#include "FrameData.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

using namespace glm;
class SkyBox_Graphics
{
public:
	SkyBox_Graphics();
	~SkyBox_Graphics();
	void DrawModel();
	virtual void InitTexture();
private:
	void LoadFaces(vector<string>);
	void LoadVAO();
	vector<GLfloat> skyboxVertices;
	vector<GLuint> skyboxIndices;
	//vector<GLuint> VBO;
	GLuint vbo;
	GLuint VBO;
	GLuint VAO;
	Shader shader;
	GLuint texture;
};
