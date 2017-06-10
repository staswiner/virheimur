#include "GL.h"



GL::GL()
{
}


GL::~GL()
{
}

void GL::DrawTriangles(GLuint VAO, GLuint numVertices)
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
	glBindVertexArray(0);
}
