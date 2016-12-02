#pragma once

#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"   

#include "Shader.h"
#include "Mesh.h"



class Model
{
public:
	/*  Functions   */
	Model();
	~Model();
	Model(GLchar* path);

	void Draw(Shader shader);
	void SignUniforms(vector<string> name, vector<string> type, vector<void*> var,
		vector<uint> TextureID, vector<string> TextureName, Shader&);
	void Draw();
	vector<Mesh> meshes;
private:
	/*  Model Data  */
	//vector<Mesh> meshes;
	string directory;
	/*  Functions   */
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	void LoadBones(uint MeshIndex, const aiMesh* pMesh, vector<Mesh::VertexBoneData> Bones);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Mesh::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};