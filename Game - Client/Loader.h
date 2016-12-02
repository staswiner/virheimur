#pragma once
//#ifdef _WIN32
//#pragma comment(lib,"glew32.lib")
//#pragma comment(lib,"assimp.lib")
//#pragma comment(lib, "DevIL.lib")
//#endif


#include <vector>
#include <map>

#include <gl/glew.h>
#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>	

#include <GLAux.h>
#include <GL/freeglut.h>
#include <SOIL.h>

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <cassert>
#include <sstream>

#include "Camera.h"
#include "Model.h"
#include "glm\glm\vec3.hpp"
#include "glm\glm\vec2.hpp"
#include "glm\glm\mat4x4.hpp"
#include "glm\glm\gtc\matrix_inverse.hpp"
#include "glm\glm\gtc\matrix_transform.hpp"
#include "glm\glm\gtc\type_ptr.hpp"
#include "Shader.h"


#define YASUO_OBJ "Yasuo/Yasuo.obj"
#define YASUO_BMP "Yasuo/Yasuo.BMP"
#define KATARINA_OBJ "Katarina/Katarina.obj"
#define KATARINA_BMP "Katarina/Katarina.BMP"
#define MAP_OBJ "Map/Map.obj"
#define MAP_BMP "Map/Map.bmp"
#define SKY_OBJ "Map/Cloud.obj"
#define SKY_BMP "Map/Map.bmp"
#define Katarina_Loaded 0
#define Yasuo_Loaded 1
#define Map_Loaded 2
#define BUFFER_OFFSET(i) ((char *)NULL + (i))


using namespace glm;
using namespace std;
class Loader
{
public:

	typedef void (Loader::*LoadModelArray) (void*);
	Loader() {}
	~Loader(void);
	virtual void DrawModel(mat4&, mat4&, mat4&, GLuint, mat4&, Shader*, unsigned int a_time = 0) {};
	virtual void DrawModel(mat4&, mat4&, mat4&, Shader&) = 0;
	virtual void DrawModel();
	virtual void DrawModelGaussic(mat4&, mat4&, mat4&, Shader&);
	virtual void LoadScene();
	virtual void InitTexture();
	virtual void Explode() {}
	virtual void Recover_Explosion() {}

	vector<Mesh::Vertex> vertices;
	vector<Mesh::Vertex> verticesSimplified;
	map<pair<int, int>, float> MappedVertices;
	vector<GLuint> indices;
	vector<vec3> verticesBox;
	float ModelSize;

	GLuint programID;
	string vShader;
	string fShader;
	string gShader;
	//GLuint VBO;
public:
	Loader(string, string); //loads 
	Loader(string, string, string); //loads 
	virtual void LoadVAO();
	virtual GLuint Setup_Program();

	string OBJ_NAME;
	string BMP_NAME;
	string SHINE_NAME;

	Model* ModelData;
	Shader shader;

	void LoadModelBox();

	GLuint VBO; // vertex buffer object
	GLuint VAO; // vertex array object
	GLuint EBO; // element buffer object
public:	GLuint texture; // texture buffer // todo remove public
		GLuint Shine;
public:
	unsigned int Vertices_Amount;
	unsigned int Indices_Amount;
//	Shader shader;
};
class Obj_Bmp_Loader : public Loader
{
public:
	virtual void LoadScene();
	Obj_Bmp_Loader() {}
	Obj_Bmp_Loader(string OBJ_NAME, string BMP_NAME)
		:Loader(OBJ_NAME, BMP_NAME)
	{
		LoadScene();
		//LoadModelBox();
		this->BMP_NAME = BMP_NAME;
		this->OBJ_NAME = OBJ_NAME;
	}
	Obj_Bmp_Loader(string OBJ_NAME, string BMP_NAME, string SHINE_NAME)
		:Loader(OBJ_NAME, BMP_NAME, SHINE_NAME)
	{
		LoadScene();
		this->SHINE_NAME = SHINE_NAME;
		this->BMP_NAME = BMP_NAME;
		this->OBJ_NAME = OBJ_NAME;
	}
	virtual void DrawModel(mat4&, mat4&, mat4&, Shader&);
	virtual void DrawModel1(mat4&, mat4&, mat4&, GLuint, mat4& LightView, Shader*);
	~Obj_Bmp_Loader() {}
	//	virtual bool isModelLoaded() const = 0;

private:

};
