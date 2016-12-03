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
#include "ShaderBuilder.h"

#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"  


#define POSITION_LOCATION    0
#define NORMAL_LOCATION      1
#define TEX_COORD_LOCATION   2
#define BONE_ID_LOCATION     3
#define BONE_WEIGHT_LOCATION 4

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
	enum VB_TYPES {
		VERTICES_BUFFER,
		BONE_VB,
		NUM_VBs
	};
	struct BoneInfo
	{
		mat4 BoneOffset;
		mat4 FinalTransformation;
	};
	struct MeshEntry {
		MeshEntry()
		{
			NumIndices = 0;
			BaseVertex = 0;
			BaseIndex = 0;
			MaterialIndex = UINT_MAX;
		}

		unsigned int NumIndices;
		unsigned int BaseVertex;
		unsigned int BaseIndex;
		unsigned int MaterialIndex;
	};

public:
	/*  Mesh Data  */
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	vector<VertexBoneData> Bones;
	/*  Functions  */
	Mesh();
	~Mesh();
	Mesh(aiMesh*, const aiScene*);
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures, vector<VertexBoneData> Bones);
	void ProcessMesh();
	//void LoadBones(uint MeshIndex, const aiMesh* pMesh, vector<Skeletal>& Bones);
	void DrawModel();

	void ReadNodeHeirarchy(float AnimationTime, const aiNode * pNode, const mat4 & ParentTransform);
	uint FindPosition(float AnimationTime, const aiNodeAnim * pNodeAnim);
	uint FindRotation(float AnimationTime, const aiNodeAnim * pNodeAnim);
	uint FindScaling(float AnimationTime, const aiNodeAnim * pNodeAnim);
	void CalcInterpolatedPosition(aiVector3D & Out, float AnimationTime, const aiNodeAnim * pNodeAnim);
	void CalcInterpolatedRotation(aiQuaternion & Out, float AnimationTime, const aiNodeAnim * pNodeAnim);
	void CalcInterpolatedScaling(aiVector3D & Out, float AnimationTime, const aiNodeAnim * pNodeAnim);
	void BoneTransform(float TimeInSeconds, vector<mat4>& Transforms);
	const aiNodeAnim * FindNodeAnim(const aiAnimation * pAnimation, const string NodeName);
	void Draw(Shader shader);
	/*  Render data  */
	GLuint VAO, VBO[NUM_VBs], EBO;
private:
	/*  Functions    */
	void setupMesh();
	void loadMesh();
	aiMesh* mesh;
	const aiScene* scene;

	map<string, uint> m_BoneMapping; // maps a bone name to its index
	uint m_NumBones;
	vector<BoneInfo> m_BoneInfo;
	mat4 m_GlobalInverseTransform;
	vector<aiAnimation*> Animations;

	vector<MeshEntry> m_Entries;
	int MeshIndex = 0;
	map<string, float> BoneMapping;

	unsigned int Vertices_Amount;
	unsigned int Indices_Amount;
	
	
};
