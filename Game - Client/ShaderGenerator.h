#pragma once
#include "Shader.h"
#include <string>
using namespace std;
class ShaderGenerator
{
public:
	ShaderGenerator();
	~ShaderGenerator();
	static Shader* GenerateShader();

private:
	static string VertexShader();
	static string GeometryShader();
	static string FragmentShader();
};

