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
	Shader(string vertexShader, string geometryShader, string fragmentShader, bool);
	enum class ImageType {
		Wire,
		Triangle
	};
	struct ShaderInfo {
		int NumDiffuse = 0;
		int NumNormalMap = 0;
		int NumSpecular = 0;
		int NumDisplacement = 0;
		bool HasMaterial = false;
		Shader::ImageType imageType = Shader::ImageType::Triangle;

		vector<GLuint> DiffuseTextures;
		vector<GLuint> NormalMaps;
	};

	static Shader* ConstructShader(ShaderInfo shaderInfo);
	// Use the program
	void Use();
	static bool LoadShaders();
	void Reload();
	static Shader& At(string ID);
private:
	Shader* ConstructShaderNS(ShaderInfo shaderInfo);
	GLuint CompileVertexShader();
	GLuint CompileGeometryShader();
	GLuint CompileFragmentShader();

	string ConstructVertexShader();
	string ConstructGeometryShader();
	string ConstructFragmentShader();

	string FileToText(string Path);
	void TextToFile(string Text,string Path);
	void OutputFinalShader(string Text, string Path);
	ShaderInfo shaderInfo;
	void InitializeShaderProgram(string Path, GLuint shaderID);
	static map<string, Shader*> mapShader;
	string VertexShaderPath, GeometryShaderPath, FragmentShaderPath;

};
