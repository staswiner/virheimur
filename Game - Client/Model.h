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
	void Draw();
	void DrawInstanced(vector<vec4>& ModelMatrix);
	int LoadTexture(string Filename);
	vector<Mesh> meshes;
private:
	/*  Model Data  */
	//vector<Mesh> meshes;
	string directory;
	/*  Functions   */
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Mesh::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	Assimp::Importer import;
	const aiScene* scene;
	string picture = "Collada/boy_10.JPG";
	vector<GLuint> Texture;
};