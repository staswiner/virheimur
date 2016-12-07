#include "Model.h"



Model::Model()
{
}
Model::Model(GLchar* Path)
{
	this->loadModel(Path);
}
Model::~Model()
{
	for each (Mesh mesh in meshes)
	{
		mesh.vertices.clear();
		mesh.indices.clear();
	}
	meshes.clear();
}
void Model::Draw(Shader shader)
{
	//for (GLuint i = 0; i < this->meshes.size(); i++)
			this->meshes[0].Draw(shader);
}
void Model::processNode(aiNode* node, const aiScene* scene)
{
	// Process all the node's meshes (if any)
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->processMesh(mesh, scene));
	}
	// Then do the same for each of its children
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene);
	}
}
Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	vector<Mesh::Vertex> vertices;
	vector<GLuint> indices;
	vector<Mesh::Texture> textures;


	//for(GLuint i=0; i < mesh->te)
	// temporary texture loading;
	Texture.push_back(LoadTexture("Collada/Tex/body01.png"));
	Texture.push_back(LoadTexture("Collada/Tex/head01.png"));
	//for (auto &m : meshes)
	//{
	//	m.m_Texture = Texture;
	//}

	return Mesh(mesh,scene);
}
void Model::loadModel(string Path)
{
	import;
	scene = import.ReadFile(Path,
		//aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		//	aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType 
		//aiProcess_ImproveCacheLocality
		);

	if (Path == "Collada/ArmyPilot.dae")
		int i = 0;
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		string Error = "ERROR::ASSIMP::";
		Error += import.GetErrorString();
		MessageBoxA(0, Error.c_str(), "", MB_OK);
		exit(0);
		return;
	}

	this->directory = Path.substr(0, Path.find_last_of('/'));

	this->processNode(scene->mRootNode, scene);
}

void Model::Draw()
{
	for (GLuint i = 0; i < this->meshes.size(); i++)
		this->meshes[i].DrawModel();
}
void Model::DrawInstanced(vector<vec4>& ModelMatrix)
{
	for (GLuint i = 0; i < this->meshes.size(); i++)
		this->meshes[i].DrawInstanced(ModelMatrix);
}
int Model::LoadTexture(string Filename)
{
	GLuint texture;
	// texture
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glGenTextures(1, &texture);
	//bind as 2d texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	int Width, Height;
	unsigned char* image;
	// "Loading Screen/UI.jpg"
	image = SOIL_load_image(Filename.c_str(), &Width, &Height, 0, SOIL_LOAD_AUTO);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//	SOIL_free_image_data(image);
	//}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	//glEnable(GL_TEXTURE_2D);
	//unbind texture 2d
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}