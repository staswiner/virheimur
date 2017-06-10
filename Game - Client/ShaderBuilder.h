#pragma once
#include <memory>
#include "Shader.h"
#include "Graphics_Header.h"
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"
#include "Material.h"
using namespace glm;

class Materials {
public:
	static Materials& GetInstance();
	Material& operator[](string s);
private:
	Materials();
	static Materials& Instance;
	map<string, Material> MaterialMap;
};
class ShaderBuilder
{
public:

	ShaderBuilder(GLuint);
	~ShaderBuilder();
	ShaderBuilder& Add_texture(string, const GLuint);
	ShaderBuilder& Add_textures(map<string,GLuint>& Textures);
	ShaderBuilder& Add_vec2(string, const vec2&);
	ShaderBuilder& Add_vec3(string, const vec3&);
	ShaderBuilder& Add_vec4(string, const vec4&);
	ShaderBuilder& Add_float(string, const float&);
	ShaderBuilder& Add_bool(string name, const bool & rhs);
	ShaderBuilder& Add_int(string, const int&);
	ShaderBuilder& Add_mat3(string, const mat3&);
	ShaderBuilder& Add_mat4(string, const mat4&);
	ShaderBuilder& Add_aimat4(string name, const aiMatrix4x4 & rhs);
	ShaderBuilder& Add_Material(string, const Material & rhs);
	static std::unique_ptr<ShaderBuilder> GetCurrentProgram();
	static std::unique_ptr<ShaderBuilder> LoadShader(Shader&);
private:
	GLuint textureCount;
	GLuint shaderID;
};

class ShaderInfo
{
public:
	ShaderInfo(GLuint);
	~ShaderInfo();
	void Add_texture(string, const GLuint);
	void Add_textures(map<string, GLuint>& Textures);
	void Add_vec2(string, const vec2&);
	void Add_vec3(string, const vec3&);
	void Add_float(string, const float&);
	void Add_bool(string name, const bool & rhs);
	void Add_int(string, int&);
	void Add_mat3(string, const mat3&);
	void Add_mat4(string, const mat4&);
	void Add_aimat4(string name, const aiMatrix4x4 & rhs);
	void Add_Material(string, const Material & rhs);
	static std::unique_ptr<ShaderBuilder> GetCurrentProgram();
	static std::unique_ptr<ShaderBuilder> LoadShader(Shader&);
private:
	//chunks of data 
	//string parse
};

