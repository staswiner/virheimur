#pragma once
#include "GL\glew.h"
#include "Mouse.h"
#include <vector>
#include "glm\glm\vec2.hpp"
#include "Shader.h"

using namespace std;
using namespace glm;
class MultiSampleFBO
{
public:
	MultiSampleFBO();
	~MultiSampleFBO();
	bool InitializeMultiSample();
	void BindFrameBuffer();
	void ChangeBuffersSize();
	void CopyBuffer(GLuint newFBO);

public:
	vector<vec2> vertices;
	unsigned int Vertices_Amount;


	GLuint texture;
	GLuint PostProcessingFBO;
	GLuint VBO;
	GLuint RBO;
};

