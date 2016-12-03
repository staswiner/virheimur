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
	ShaderBuilder& Add_texture(string, GLuint);
	ShaderBuilder& Add_vec2(string,vec2&);
	ShaderBuilder& Add_vec3(string, vec3&);
	ShaderBuilder& Add_float(string, float&);
	ShaderBuilder& Add_int(string, int&);
	ShaderBuilder& Add_mat3(string,mat3&);
	ShaderBuilder& Add_mat4(string,mat4&);
	ShaderBuilder & Add_aimat4(string name, aiMatrix4x4 & rhs);
	static std::unique_ptr<ShaderBuilder> LoadShader(Shader&);
private:
	GLuint textureCount;
	GLuint shaderID;
};

