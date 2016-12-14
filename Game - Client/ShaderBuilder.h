#pragma once
#include <memory>
#include "Shader.h"
#include "Graphics_Header.h"
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"  
using namespace glm;
class ShaderBuilder
{
public:
	ShaderBuilder(GLuint);
	~ShaderBuilder();
	ShaderBuilder& Add_texture(string, const GLuint);
	ShaderBuilder& Add_textures(map<string,GLuint>& Textures);
	ShaderBuilder& Add_vec2(string, const vec2&);
	ShaderBuilder& Add_vec3(string, const vec3&);
	ShaderBuilder& Add_float(string, const float&);
	ShaderBuilder& Add_bool(string name, const bool & rhs);
	ShaderBuilder& Add_int(string, int&);
	ShaderBuilder& Add_mat3(string, const mat3&);
	ShaderBuilder& Add_mat4(string, const mat4&);
	ShaderBuilder& Add_aimat4(string name, const aiMatrix4x4 & rhs);
	static std::unique_ptr<ShaderBuilder> GetCurrentProgram();
	static std::unique_ptr<ShaderBuilder> LoadShader(Shader&);
private:
	GLuint textureCount;
	GLuint shaderID;
};

