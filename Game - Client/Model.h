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
	Model(GLchar* path, string CollisionType);

	Model(Mesh& mesh);

	void Draw();
	void DrawInstanced(vector<mat4>& ModelMatrix);
	int LoadTexture(string Filename);
	void AddTexture(string TextureName,string Filename);
	static vector<vector<int>> LoadBufferFromImage(string Filename);
	vector<Mesh> meshes;
	map<string,GLuint> Textures;
	vector<Materials> m_Materials;

	Mesh::BoundryBox boundryBox;
	struct ShaderParams
	{
		Shader* MainShader;
		bool isAnimated;
		int numTextures;
	};
	ShaderParams shaderParams;

private:
	/*  Model Data  */
	//vector<Mesh> meshes;
	string directory;
	/*  Functions   */
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	void CreateShader();
	void loadModel(Mesh& mesh);
	vector<Mesh::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	Assimp::Importer import;
	const aiScene* scene;
	string picture = "Collada/boy_10.JPG";
	vector<GLuint> Texture;
	string CollisionType;
	string ModelName;
	string LastDateOfChange;
};