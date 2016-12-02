#pragma once
#include "GL\glew.h"
#include "Mouse.h"
#include <vector>
#include "glm\glm\vec2.hpp"
#include "Shader.h"

using namespace std;
using namespace glm;
class PreEffect
{
public:
	PreEffect();
	bool Initialize();
	void BindFrameBuffer();
	void DrawFrameBuffer();
	void ChangeBuffersSize();
	~PreEffect();

private:
	void Load_VAO();
	void Draw_Interface();
	void Load_Interface();
	vector<vec2> vertices;
	unsigned int Vertices_Amount;


	GLuint texture;
	GLuint PreEffectFBO;
	GLuint VAO;
	GLuint VBO;
	GLuint RBO;
	Shader shader;

};

