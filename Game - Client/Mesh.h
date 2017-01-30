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

#include "Collision.h"
#include "Ground_Collision.h"
#include "Structures.h"


#define POSITION_LOCATION    0
#define NORMAL_LOCATION      1
#define TEX_COORD_LOCATION   2
#define BONE_ID_LOCATION     3
#define BONE_WEIGHT_LOCATION 4
#define MODEL_MAT_LOCATION	 5

using namespace glm;
using namespace std;
class Mesh {
public:
	
	struct Texture {
		GLuint id;
		string type;
	};
	struct Skeletal {
		vec3 Weight;
		int Index;
	};
	struct VertexBoneData {
		uint IDs[4];
		float Weights[4];
		void AddBoneData(uint BoneID, float Weight);
	};
	enum VB_TYPES {
		VERTICES_BUFFER,
		NORMALS_BUFFER,
		UVS_BUFFER,
		BONE_VB,
		MODEL_VB,
		NUM_VBs
	};
	struct BoneInfo
	{
		aiMatrix4x4 BoneOffset;
		aiMatrix4x4 FinalTransformation;
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
	vector<Stas::Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	vector<VertexBoneData> Bones;
	/*  Functions  */
	Mesh();
	~Mesh();
	Mesh(aiMesh*, const aiScene*, string Collision);
	void LoadCustom(vector<Stas::Vertex>& Vertices);
	void ProcessMesh();
	//void LoadBones(uint MeshIndex, const aiMesh* pMesh, vector<Skeletal>& Bones);
	void DrawModel();
	void DrawInstanced(vector<mat4>& ModelMatrix);

	void ReadNodeHeirarchy(double AnimationTime, const aiNode * pNode, const aiMatrix4x4 & ParentTransform);
	uint FindPosition(double AnimationTime, const aiNodeAnim * pNodeAnim);
	uint FindRotation(double AnimationTime, const aiNodeAnim * pNodeAnim);
	uint FindScaling(double AnimationTime, const aiNodeAnim * pNodeAnim);
	void CalcInterpolatedPosition(aiVector3D & Out, float AnimationTime, const aiNodeAnim * pNodeAnim);
	void CalcInterpolatedRotation(aiQuaternion & Out, float AnimationTime, const aiNodeAnim * pNodeAnim);
	void CalcInterpolatedScaling(aiVector3D & Out, float AnimationTime, const aiNodeAnim * pNodeAnim);
	void BoneTransform(double TimeInSeconds, vector<aiMatrix4x4>& Transforms);
	const aiNodeAnim * FindNodeAnim(const aiAnimation * pAnimation, const string NodeName);
	int LoadTexture(string Filename);
	void Draw(Shader shader);
	/*  Render data  */
	GLuint VAO, VBO[NUM_VBs], EBO;
private:
	/*  Functions    */
	void setupMesh();
	void setupMeshCustom();
	void loadMesh();
	aiMesh* mesh;
	const aiScene* scene;

	uint m_NumBones;
	vector<BoneInfo> m_BoneInfo;
	mat4 m_GlobalInverseTransform;
	vector<aiAnimation*> Animations;
	map<string, float> m_BoneMapping;

	vector<MeshEntry> m_Entries;
	int MeshIndex = 0;
public:
	unsigned int Vertices_Amount;
	unsigned int Indices_Amount;
public:
	vector<GLuint> m_Texture;
	string CollisionType;
	Collision* mCollision;
};
