#pragma once
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "glm\glm\mat4x4.hpp"
#include "glm\glm\vec2.hpp"
#include "glm\glm\vec3.hpp"
#include "glm\glm\gtc\matrix_transform.hpp"
#include "glm\glm\gtc\type_ptr.hpp"
#include "SOIL.h"
#include <vector>
#include <sstream>
#include "Models_Header.h"
#include "Camera.h"
#include <Vfw.h>
#include "ShaderBuilder.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

using namespace glm;
using namespace std;
class Loading_Screen
{
public:
	Loading_Screen() {}
	Loading_Screen(vec2 WindowSize, HDC);
	~Loading_Screen();
	void Draw_Loading_Screen();
private:
	void Load_Loading_Animation();
	void Load_VAO();
	void OpenAVI(string);

	GLuint VAO, VBO, Texture[36];
	Shader shader;

	HDC m_HDC;
	mat4 Orthographic_Projection;
	vector<vec2> vertices;
	unsigned int Vertices_Amount;
	
	Loader* L_Loading_Screen;
	// Video
	PAVISTREAM pavi;	// Handle To An Open Stream
};

