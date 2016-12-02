#pragma once
#include "GL\glew.h"
#include "Mouse.h"
#include <vector>
#include "glm\glm\vec2.hpp"
#include "Shader.h"


using namespace std;
using namespace glm;
class FBO
{
public:
	FBO();
	bool Initialize(int Height,int Width, Shader&);
	void BindFrameBuffer();
	static void UnbindFrameBuffer();
	void DrawFrameBuffer();
	void DrawDirectly(vector<GLuint>,vector<string>);
	void ChangeBuffersSize();
	~FBO();

public:
	void Load_VAO();
	void Draw_Interface();
	void Load_Interface(Shader&);
	vector<vec2> vertices;
	unsigned int Vertices_Amount;


	GLuint texture;
	GLuint PostProcessingFBO;
	GLuint VAO;
	GLuint VBO;
	GLuint RBO;
	Shader shader;
	GLint Width, Height;

};

