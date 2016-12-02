#pragma once
#include "Loader.h"
#include "Shader.h"
class SkyBox : public Loader
{
public:
	SkyBox();
	~SkyBox();
	void DrawModel(mat4&, mat4&, mat4&, GLuint, mat4&, Shader*, uint);
	void DrawModel(mat4&, mat4&, mat4&, GLuint) {}
	virtual void InitTexture();
private:
	void LoadFaces(vector<string>);
	static void CalculateDelta();
	void LoadVAO();
	vector<GLfloat> skyboxVertices;
	vector<GLuint> skyboxIndices;
	//vector<GLuint> VBO;
	GLuint vbo;
	Shader skyboxShader;
	static unsigned int TimePassed;
	float find_height_at(float x, float z) { return 0; };
	void DrawModel(mat4&, mat4&, mat4&, Shader&) {}
};
