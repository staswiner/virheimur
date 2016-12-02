#pragma once
#include "Graphics_Header.h"
#include "Shader.h"
#include <vector>
#include <complex>
using namespace glm;
using namespace std;
class MathGrass
{
public:
	MathGrass();
	~MathGrass();
	void Init();
	void Draw(mat4& Perspective);
	vector<vec3> vertices;
	Shader* shader;
private:
	GLuint VAO,VBO;
	void Fractal(complex<float> z, float factor);
	vector<vec2> FractalCoords;
	vector<vector<float>> bitMap;
};

