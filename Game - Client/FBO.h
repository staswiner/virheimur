#pragma once
#include "GL\glew.h"
#include "Mouse.h"
#include <vector>
#include "glm\glm\vec2.hpp"
#include "glm\glm\vec4.hpp"
#include "Shader.h"
#include "GL.h"

using namespace std;
using namespace glm;

class FBO
{
public:
	FBO();
	bool Initialize(float Height,float Width, Shader*);
	bool InitializeBig(int Height, int Width, Shader * shader);
	void BindFrameBuffer();
	static void UnbindFrameBuffer();
	void DrawFrameBuffer();
	void DrawFrameBuffer(int Top, int Left, int Width, int Height);
	/*combines multiple textures*/
	void DrawMultipleTextures(vector<GLuint> TextureIDs,vector<string> TextureUniformNames);
	void ChangeBuffersSize();
	void Resize(float Width, float Height);
	vec4 GetPixel(int x, int y);
	~FBO();

public:
	void Load_VAO();
	void Load_Interface(Shader*);
	struct Vertices {
		Vertices(vec2 Position, vec2 UVs) { this->Position = Position; this->UVs = UVs; }
		vec2 Position;
		vec2 UVs;
	};
	vector<Vertices> vertices;
	unsigned int Vertices_Amount;
	GLuint texture;
	GLuint ID;
	GLuint VAO;
	GLuint VBO;
	GLuint RBO;
	Shader* shader;
	GLint Width, Height;
private:
	void Draw_Interface();
};

