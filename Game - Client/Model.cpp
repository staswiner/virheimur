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

void Model::LoadBones(uint MeshIndex, const aiMesh * pMesh, vector<Mesh::VertexBoneData> Bones)
{
//	//
//	/*Local Variables made for member variables*/
//	map<string, GLuint> m_BoneMapping;
//	//
//	for (uint i = 0; i < pMesh->mNumBones; i++) {
//		GLuint m_NumBones = pMesh->mNumBones;
//		uint BoneIndex = 0;
//		string BoneName(pMesh->mBones[i]->mName.data);
//
//		if (m_BoneMapping.find(BoneName) == m_BoneMapping.end()) {
//			BoneIndex = m_NumBones;
//			m_NumBones++;
//			BoneInfo bi;
//			m_BoneInfo.push_back(bi);
//		}
//		else {
//			BoneIndex = m_BoneMapping[BoneName];
//		}
//
//		m_BoneMapping[BoneName] = BoneIndex;
//		m_BoneInfo[BoneIndex].BoneOffset = pMesh->mBones[i]->mOffsetMatrix;
//
//		for (uint j = 0; j < pMesh->mBones[i]->mNumWeights; j++) {
//			uint VertexID = m_Entries[MeshIndex].BaseVertex + pMesh->mBones[i]->mWeights[j].mVertexId;
//			float Weight = pMesh->mBones[i]->mWeights[j].mWeight;
//			Bones[VertexID].AddBoneData(BoneIndex, Weight);
//		}
//	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	vector<Mesh::Vertex> vertices;
	vector<GLuint> indices;
	vector<Mesh::Texture> textures;

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Mesh::Vertex vertex;
		vec3 Position(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vec3 Normals;
		if (mesh->mNormals != NULL)
			Normals = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		vec2 UVs;
		if (mesh->mTextureCoords[0])
			UVs = vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);

		vertex.Position = Position;
		if (&mesh->mNormals[i] != nullptr)
		vertex.Normal = Normals;
		vertex.TexCoords = UVs;
		vertices.push_back(vertex);
	}
	// Process indices
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		indices.push_back(mesh->mFaces[i].mIndices[0]);
		indices.push_back(mesh->mFaces[i].mIndices[1]);
		indices.push_back(mesh->mFaces[i].mIndices[2]);
	}
	// Process material
	if (mesh->mMaterialIndex >= 0)
	{
		
	}
	GLuint a = scene->mNumMaterials;
	//for(GLuint i=0; i < mesh->te)


	// Process Bones
	vector<Mesh::BoneInfo> m_BoneInfo;
	vector<Mesh::MeshEntry> m_Entries;
	int MeshIndex = 0;
	map<string, float> BoneMapping;
	vector<Mesh::VertexBoneData> Bones;
	Bones.resize(mesh->mNumVertices);
	for (uint i = 0; i < mesh->mNumBones; i++) 
	{
		uint BoneIndex = 0;
		string BoneName(mesh->mBones[i]->mName.data);

		if (BoneMapping.find(BoneName) == BoneMapping.end()) 
		{
			// Allocate an index for a new bone
			BoneIndex = BoneMapping.size();
			Mesh::BoneInfo bi;
			memcpy(&bi, &mesh->mBones[i]->mOffsetMatrix, 16 * 2);
			m_BoneInfo.push_back(bi);
			BoneMapping[BoneName] = BoneIndex;
		}
		else 
		{
			BoneIndex = BoneMapping[BoneName];
		}

		for (uint j = 0; j < mesh->mBones[i]->mNumWeights; j++) {
			uint VertexID = /*m_Entries[MeshIndex].BaseVertex + incase there are several meshes*/ mesh->mBones[i]->mWeights[j].mVertexId;
			float Weight = mesh->mBones[i]->mWeights[j].mWeight;
			Bones[VertexID].AddBoneData(BoneIndex, Weight);
		}
	}
	return Mesh(mesh,scene);
	return Mesh(vertices, indices, textures, Bones);
}
void Model::loadModel(string Path)
{
	import;
	scene = import.ReadFile(Path,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		//	aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType
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
