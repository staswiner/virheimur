#include "ShaderBuilder.h"



ShaderBuilder::ShaderBuilder(GLuint shaderID)
{
	textureCount = 0;
	this->shaderID = shaderID;
}


ShaderBuilder::~ShaderBuilder()
{
}

ShaderBuilder & ShaderBuilder::Add_texture(string str, GLuint texID)
{
	GLuint result = glGetUniformLocation(shaderID, str.c_str());
	glUniform1i(result, textureCount);
	glActiveTexture(GL_TEXTURE0 + textureCount);
	glBindTexture(GL_TEXTURE_2D, texID);
	textureCount++;
	return *this;
}

ShaderBuilder & ShaderBuilder::Add_textures(map<string, GLuint>& Textures)
{
	// TODO: insert return statement here
	for (auto t : Textures)
	{
		this->Add_texture(t.first, t.second);
	}
	return *this;
}

ShaderBuilder & ShaderBuilder::Add_vec2(string name, const vec2 & rhs)
{
	// TODO: insert return statement here
	glUniform2f(glGetUniformLocation(shaderID, name.c_str()),rhs.x, rhs.y);
	return *this;
}

ShaderBuilder & ShaderBuilder::Add_vec3(string name, const vec3 & rhs)
{
	// TODO: insert return statement here
	glUniform3f(glGetUniformLocation(shaderID, name.c_str()), rhs.x, rhs.y, rhs.z);
	return *this;
}

ShaderBuilder & ShaderBuilder::Add_float(string name, const float & rhs)
{
	// TODO: insert return statement here
	glUniform1f(glGetUniformLocation(shaderID, name.c_str()), rhs);
	return *this;
}
ShaderBuilder & ShaderBuilder::Add_bool(string name, const bool & rhs)
{
	// TODO: insert return statement here
	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), rhs);
	return *this;
}

ShaderBuilder & ShaderBuilder::Add_int(string name, int & rhs)
{
	// TODO: insert return statement here
	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), rhs);
	return *this;
}

ShaderBuilder & ShaderBuilder::Add_mat3(string name, const mat3 & rhs)
{
	// TODO: insert return statement here
	glUniformMatrix3fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, value_ptr(rhs));
	return *this;
}

ShaderBuilder & ShaderBuilder::Add_mat4(string name, const mat4 & rhs)
{
	// TODO: insert return statement here
	glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, value_ptr(rhs));
	return *this;
}

ShaderBuilder & ShaderBuilder::Add_aimat4(string name, const aiMatrix4x4 & rhs)
{
	// TODO: insert return statement here
	glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_TRUE, (const GLfloat*)&rhs);
	return *this;
}

ShaderBuilder & ShaderBuilder::Add_Material(string name, const Material & rhs)
{
	this->Add_vec3(name+".ambient", rhs.ambient).
	Add_vec3(name + ".diffuse", rhs.diffuse).
	Add_vec3(name + ".specular", rhs.specular).
	Add_float(name + "shininess", rhs.shininess);
	return *this;
}

std::unique_ptr<ShaderBuilder> ShaderBuilder::GetCurrentProgram()
{
	GLint id;
	glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	ShaderBuilder shaderBuilder(id);
	return std::make_unique<ShaderBuilder>(shaderBuilder);
}

std::unique_ptr<ShaderBuilder> ShaderBuilder::LoadShader(Shader & shader)
{
	// TODO: insert return statement here
	//glUseProgram(0);
	shader.Use();
	ShaderBuilder shaderBuilder(shader.ProgramID);
	return std::make_unique<ShaderBuilder>(shaderBuilder);
}

Materials & Materials::GetInstance()
{
	static Materials Instance;
	return Instance;
}

Material & Materials::operator[](string s) 
{
	return this->MaterialMap[s];
}

Materials::Materials()
{
	MaterialMap["chrome"] = { vec3(0.25f),vec3(0.4f),vec3(0.774597f),0.6f };
	MaterialMap["shiny"] = {vec3(1),vec3(1),vec3(1),0.2f };
	MaterialMap["emerald"] = { vec3(0.0215,0.1745,0.0215),vec3(0.07568,0.61424,0.07568),vec3(0.633,0.727811,0.633),0.6f };
	MaterialMap["water"] = { vec3(0.2,0.25,0.4),vec3(0.4f),vec3(0.633,0.727811,0.633),0.6f };
}
