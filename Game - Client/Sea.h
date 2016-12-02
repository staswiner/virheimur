#pragma once
#include <vector>

#include "GL\glew.h"
#include "glm\glm\vec3.hpp"
#include "glm\glm\mat4x4.hpp"
#include "glm\glm\gtc\type_ptr.hpp"
#include "glm\glm\gtc\matrix_transform.hpp"
#include "Shader.h"
#include "Mouse.h"
#include "Camera.h"
#include "SOIL.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
using namespace glm;
using namespace std;
class Sea
{
public:
	Sea();
	~Sea();
	void Draw(mat4& ProjectionMat, mat4& ViewMat, mat4& ModelMat);
	void Initialize();
	void InitializeRefraction();
	void InitializeReflection();
	void BindRefraction();
	void BindReflection();
	Shader sReflection_Ground;
	Shader sRefraction_Ground;
	Shader sUnit;
private:
	void Load_Shader();
	void Load_VAO();
	void Load_World_Shaders();

	Shader shader;
	GLuint ViewportTexture;
	GLuint ReflectionTexture;
	GLuint VAO;
	GLuint VBO;
	GLuint Vertices_Amount;
	GLuint ViewportFBO;
	GLuint ReflectionFBO;
	GLuint ViewportRBO;
	GLuint ReflectionRBO;

	GLuint DUDVtexture;
	GLuint NormalMap;
	struct Vertices
	{
		vec3 position;
		vec2 texture;
	};
	vector<Vertices> vertices;
};

