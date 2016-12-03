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
	// TODO: insert return statement here
	glActiveTexture(GL_TEXTURE0 + textureCount);
	glBindTexture(GL_TEXTURE_2D, texID);
	GLuint result = glGetUniformLocation(shaderID, str.c_str());
	glUniform1i(glGetUniformLocation(shaderID, str.c_str()), textureCount);
	textureCount++;
	return *this;
}

ShaderBuilder & ShaderBuilder::Add_vec2(string name,vec2 & rhs)
{
	// TODO: insert return statement here
	glUniform2f(glGetUniformLocation(shaderID, name.c_str()),rhs.x, rhs.y);
	return *this;
}

ShaderBuilder & ShaderBuilder::Add_vec3(string name,vec3 & rhs)
{
	// TODO: insert return statement here
	glUniform3f(glGetUniformLocation(shaderID, name.c_str()), rhs.x, rhs.y, rhs.z);
	return *this;
}

ShaderBuilder & ShaderBuilder::Add_float(string name, float & rhs)
{
	// TODO: insert return statement here
	glUniform1f(glGetUniformLocation(shaderID, name.c_str()), rhs);
	return *this;
}

ShaderBuilder & ShaderBuilder::Add_int(string name, int & rhs)
{
	// TODO: insert return statement here
	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), rhs);
	return *this;
}

ShaderBuilder & ShaderBuilder::Add_mat3(string name, mat3 & rhs)
{
	// TODO: insert return statement here
	glUniformMatrix3fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, value_ptr(rhs));
	return *this;
}

ShaderBuilder & ShaderBuilder::Add_mat4(string name, mat4 & rhs)
{
	// TODO: insert return statement here
	glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, value_ptr(rhs));
	return *this;
}

ShaderBuilder & ShaderBuilder::Add_aimat4(string name, aiMatrix4x4 & rhs)
{
	// TODO: insert return statement here
	glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_TRUE, (const GLfloat*)&rhs);
	return *this;
}

std::unique_ptr<ShaderBuilder> ShaderBuilder::LoadShader(Shader & shader)
{
	// TODO: insert return statement here
	shader.Use();
	ShaderBuilder shaderBuilder(shader.ProgramID);
	return std::make_unique<ShaderBuilder>(shaderBuilder);
}
