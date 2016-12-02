#include "MathGrass.h"



MathGrass::MathGrass()
{
	vertices.push_back(vec3(0, 0, 0));
	vertices.push_back(vec3(1, 0, 0));
	vertices.push_back(vec3(0, 1, 0));
	shader = new Shader("Basic Vertex Shader.glsl",
		/*	"MathGrass Geometry Shader.glsl",*/
		"Basic Fragment Shader.glsl");
	//Fractal(complex<float>(0, 0), 1.0f);
	//bitMap.resize(800);
	//for (int x = 0; x < 800; x++)
	//{
	//	bitMap[x].resize(600);
	//}
	//for (int x = 0; x < 800; x++)
	//{
	//	for (int y = 0; y < 600; y++)
	//	{
	//		bitMap[x][y] = 0;
	//	}
	//}
	//for (int i = 0; i < FractalCoords.size(); i++)
	//{
	//	bitMap[FractalCoords[i].x * 400.0f][FractalCoords[i].y * 300.0f] = 1.0f;
	//}
}


MathGrass::~MathGrass()
{
}
void MathGrass::Init()
{
	/*glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (char*)NULL);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);*/
	vertices.push_back(vec3(-1 * 10, -1 * 10,0));
	vertices.push_back(vec3( 1 * 10, -1 * 10, 0));
	vertices.push_back(vec3(-1 * 10,  1 * 10, 0));

	vertices.push_back(vec3( 1 * 10,  1 * 10, 0));
	vertices.push_back(vec3( 1 * 10, -1 * 10, 0));
	vertices.push_back(vec3(-1 * 10,  1 * 10, 0));

	// generate buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind arrays
	glBindVertexArray(VAO);
	// bind vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices.front(), GL_STATIC_DRAW);

	// vertices
	/// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (char*)NULL);
	glEnableVertexAttribArray(0);

	// Unbind VAO
	glBindVertexArray(0);
}

void MathGrass::Draw(mat4& Perspective)
{
	shader->Use();
	glUniformMatrix4fv(glGetUniformLocation(shader->ProgramID, "projection"), 1, GL_FALSE, value_ptr(Perspective));
	glUniformMatrix4fv(glGetUniformLocation(shader->ProgramID, "view"), 1, GL_FALSE, value_ptr(mat4()));
	glUniformMatrix4fv(glGetUniformLocation(shader->ProgramID, "model"), 1, GL_FALSE, value_ptr(mat4()));
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size() * 3);
	glBindVertexArray(0);
}
void MathGrass::Fractal(complex<float> z, float factor)
{
	if (z.real() > 1.0f)
	{
		int i = 0;
	}
	complex<float> Z0(0.2, 0.5);
	if (abs(z*z) + abs(Z0) >= 2.0f)
		return;
	if (factor <= 0.01f)
		return;
	FractalCoords.push_back(vec2(z.real(), z.imag()));
	factor /= 2.0f;
	if (abs(z*z) - 1.0f < 2.0f)
	{
		Fractal(complex<float>(z.real() + factor, z.imag()), factor);
		Fractal(complex<float>(z.real() - factor, z.imag()), factor);
		Fractal(complex<float>(z.real(), z.imag() + factor), factor);
		Fractal(complex<float>(z.real(), z.imag() - factor), factor);
	}
	return;
}