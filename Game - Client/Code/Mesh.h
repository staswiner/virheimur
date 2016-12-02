#pragma once
#include <vector>
#include <sstream>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>			// Header File For The OpenGL32 Library
#include <GL/glu.h>	
#include <GLAux.h>
#include <GL/freeglut.h>
#include <vector>

#include "glm/glm/vec3.hpp"
#include "glm/glm/vec2.hpp"
#include "glm\glm\mat4x4.hpp"
#include "Mouse.h"
#include "glm\glm\gtc\matrix_transform.hpp"
#include "glm\glm\gtc\type_ptr.hpp"
#include "Shader.h"
using namespace glm;
using namespace std;
class Mesh {
public:
	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};
	struct Texture {
		GLuint id;
		string type;
	};
	struct Skeletal {
		vec3 Weight;
		int Index;
	};
	struct VertexBoneData {
		uint IDs[2];
		float Weights[2];
		void AddBoneData(uint BoneID, float Weight);
	};
public:
	/*  Mesh Data  */
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	/*  Functions  */
	Mesh();
	~Mesh();
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
	//void LoadBones(uint MeshIndex, const aiMesh* pMesh, vector<Skeletal>& Bones);
	void DrawModel();

	void SignUniforms(vector<string> name, vector<string> type, vector<void*> var,
		vector<uint> TextureID, vector<string> TextureName, Shader&);
	void Draw(Shader shader);
	/*  Render data  */
	GLuint VAO, VBO, EBO;
private:
	/*  Functions    */
	void setupMesh();
	void loadMesh();
		 
	unsigned int Vertices_Amount;
	unsigned int Indices_Amount;
};
