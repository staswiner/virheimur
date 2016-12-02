#include "Load_FBX_file.h"



Load_FBX_file::Load_FBX_file()
{
}
Load_FBX_file::Load_FBX_file(string FileName)
{
	this->OBJ_NAME = FileName;
	LoadFile();
}

Load_FBX_file::~Load_FBX_file()
{
	if (ModelData != NULL)
	{
		delete ModelData;
	}
}

void Load_FBX_file::DrawModel(mat4 &, mat4 &, mat4 &)
{
	this->ModelData->Draw(Shader("Loading_Screen Vertex Shader.glsl","Loading_Screen Fragment Shader.glsl"));
}

void Load_FBX_file::LoadFile()
{
	ModelData = new Model((GLchar*)OBJ_NAME.c_str());
	int i = 0;
}
