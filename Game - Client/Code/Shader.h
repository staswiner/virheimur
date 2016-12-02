#pragma once
#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <map>
#include <utility>

using namespace std;
class Shader
{
public:
	// The program ID
	GLuint ProgramID;
	// Constructor reads and builds the shader
	Shader();
	~Shader();
	Shader(string vertexPath,string fragmentPath);
	Shader(string vertexPath, string geometryPath, string fragmentPath);
	// Use the program
	void Use();
	static bool LoadShaders();
	static Shader& At(string ID);
private:
	static map<string, Shader*> mapShader;

};