#pragma once
#include "Graphics_Header.h"
class GL
{
public:
	GL();
	~GL();
	static void DrawTriangles(GLuint VAO, GLuint numVertices);
};

