#pragma once
#include "Loader.h"
class Ground : public Obj_Bmp_Loader
{
public:
	Ground();
	~Ground();
	//virtual void DrawModel(mat4&, mat4&, mat4&, GLuint, mat4&, Shader*);
	//void LoadScene();
	virtual void InitTexture();
	virtual void DrawModel(mat4&, mat4&, mat4&, GLuint, mat4& LightView, Shader*, unsigned int);
	GLuint GrassTexture;
	GLuint MountainTexture;

private:
	void CreateHeightMap();
};
