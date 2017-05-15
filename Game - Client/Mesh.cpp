#include "Mesh.h"

Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}
Mesh::Mesh(aiMesh * mesh, const aiScene* scene, string CollisionType)
{
	this->mesh = mesh;
	this->scene = scene;
	this->CollisionType = CollisionType;
	
	ProcessMesh();
}
void Mesh::LoadCustom(vector<Stas::Vertex>& Vertices)
{
	vertices = Vertices;
	/*vector<Stas::Vertex> Vertexes;
	for (auto v : Vertices)
	{
		
		Vertexes.push_back(v.Position);
	}*/
	if (this->CollisionType == "Ground")
		mCollision = new Ground_Collision(Vertices);
	Bones.resize(1);
	//GLuint a = scene->mNumMaterials;
	//for(GLuint i=0; i < mesh->te)


	// Process Bones
	this->setupMeshCustom();
}
void Mesh::ProcessMesh()
{
	//for (GLuint i = 0; i < mesh->mNumVertices; i++)
	//{
	//	Stas::Vertex vertex;
	//	vec3 Position(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
	//	vec3 Normals;
	//	if (mesh->mNormals != NULL)
	//		Normals = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
	//	vec2 UVs;
	//	if (mesh->mTextureCoords[0])
	//		UVs = vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);

	//	vertex.Position = Position;
	//	if (&mesh->mNormals[i] != nullptr)
	//		vertex.Normal = Normals;
	//	vertex.TexCoords = UVs;
	//	vertices.push_back(vertex);
	//}
	
	// Bitangent tangent normal 
	//for (GLuint i = 0; i < mesh->mNumVertices; i++)
	//{
	//	// positions
	//	glm::vec3 pos1(-1.0, 1.0, 0.0);
	//	glm::vec3 pos2(-1.0, -1.0, 0.0);
	//	glm::vec3 pos3(1.0, -1.0, 0.0);
	//	// texture coordinates
	//	glm::vec2 uv1(0.0, 1.0);
	//	glm::vec2 uv2(0.0, 0.0);
	//	glm::vec2 uv3(1.0, 0.0);
	//	glm::vec2 uv4(1.0, 1.0);
	//	// normal vector
	//	glm::vec3 nm(0.0, 0.0, 1.0);

	//	glm::vec3 edge1 = pos2 - pos1;
	//	glm::vec3 edge2 = pos3 - pos1;
	//	glm::vec2 deltaUV1 = uv2 - uv1;
	//	glm::vec2 deltaUV2 = uv3 - uv1;


	//	GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
	//	vec3 tangent1;
	//	tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	//	tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	//	tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	//	tangent1 = glm::normalize(tangent1);
	//}
	if (this->CollisionType == "Ground")
	{
		vector<Stas::Vertex> Vertices;
		for (GLuint i = 0; i < mesh->mNumVertices; i++)
		{
			Stas::Vertex vertex;
			vertex.Position = vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
			vertex.Normal = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

			Vertices.push_back(vertex);
		}

		mCollision = new Ground_Collision(Vertices);
	}

	//// Process indices
	//for (GLuint i = 0; i < mesh->mNumFaces; i++)
	//{
	//	indices.push_back(mesh->mFaces[i].mIndices[0]);
	//	indices.push_back(mesh->mFaces[i].mIndices[1]);
	//	indices.push_back(mesh->mFaces[i].mIndices[2]);
	//}
	// Process material
	if (mesh->mMaterialIndex >= 0)
	{
		mesh;
	}
	// Textures


	//GLuint a = scene->mNumMaterials;
	//for(GLuint i=0; i < mesh->te)


	// Process Bones
	
	Bones.resize(mesh->mNumVertices);
	for (uint i = 0; i < mesh->mNumBones; i++)
	{
		uint BoneIndex = 0;
		string BoneName(mesh->mBones[i]->mName.data);

		if (m_BoneMapping.find(BoneName) == m_BoneMapping.end())
		{
			// Allocate an index for a new bone
			BoneIndex = m_BoneMapping.size();
			BoneInfo bi;
			bi.BoneOffset = mesh->mBones[i]->mOffsetMatrix;
			m_BoneInfo.push_back(bi);
			//memcpy(&bi, &mesh->mBones[i]->mOffsetMatrix.Transpose(), 16 * sizeof(float));
			//m_BoneInfo.push_back(bi);
			m_BoneMapping[BoneName] = BoneIndex;
		}
		else
		{
			BoneIndex = m_BoneMapping[BoneName];
		}

		for (uint j = 0; j < mesh->mBones[i]->mNumWeights; j++) {
			uint VertexID =/* mesh->mNumVertices + */mesh->mBones[i]->mWeights[j].mVertexId;
			float Weight = mesh->mBones[i]->mWeights[j].mWeight;
			Bones[VertexID].AddBoneData(BoneIndex, Weight);
		}
	}
	for (uint i = 0; i < scene->mNumAnimations; i++)
	{
		Animations.push_back(scene->mAnimations[i]);
	}
	this->LoadMaterial();
	this->setupMesh();
	vertices.clear();
	indices.clear();
	Animations.clear();
}
void Mesh::setupMesh()
{
	Vertices_Amount = mesh->mNumVertices;
	Indices_Amount = indices.size();
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(sizeof(VBO)/sizeof(VBO[0]), this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);
	/*glBindBuffer(GL_ARRAY_BUFFER, this->VBO[);

	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex),
		&this->vertices.front(), GL_STATIC_DRAW);*/
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint),
	&this->indices[0], GL_STATIC_DRAW);*/

	// Vertices
	glEnableVertexAttribArray(POSITION_LOCATION);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[VERTICES_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mesh->mVertices[0]) * mesh->mNumVertices, mesh->mVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(aiVector3D),
		(GLvoid*)0);

	// Normals
	glEnableVertexAttribArray(NORMAL_LOCATION);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[NORMALS_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mesh->mNormals[0]) * mesh->mNumVertices, mesh->mNormals, GL_STATIC_DRAW);
	glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(aiVector3D),
		(GLvoid*)0);

	// Texture Coords
	glEnableVertexAttribArray(TEX_COORD_LOCATION);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[UVS_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mesh->mTextureCoords[0][0]) * mesh->mNumVertices, mesh->mTextureCoords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, sizeof(aiVector3D),
		(GLvoid*)0);

	// Bone Data
	glBindBuffer(GL_ARRAY_BUFFER, VBO[BONE_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Bones[0]) * Bones.size(), &Bones[0], GL_STATIC_DRAW);
	glVertexAttribIPointer(BONE_ID_LOCATION, 4, GL_INT, sizeof(VertexBoneData), (const GLvoid*)0);
	glEnableVertexAttribArray(BONE_ID_LOCATION);
	glVertexAttribPointer(BONE_WEIGHT_LOCATION, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), 
		(const GLvoid*)16);
	glEnableVertexAttribArray(BONE_WEIGHT_LOCATION);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[MODEL_VB]);
	/*glVertexAttribPointer(MODEL_MAT_LOCATION, 4, GL_FLOAT, GL_FALSE, sizeof(vec4),
		(const GLvoid*)0);
	glEnableVertexAttribArray(MODEL_MAT_LOCATION);
	glVertexAttribDivisor(MODEL_MAT_LOCATION, 1);
	*/
	for (GLuint i = 0; i < 4; i++) 
	{
		glVertexAttribPointer(MODEL_MAT_LOCATION + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), 
			(const GLvoid*)(sizeof(vec4) * i));
		glEnableVertexAttribArray(MODEL_MAT_LOCATION + i);
		glVertexAttribDivisor(MODEL_MAT_LOCATION + i, 1);
	}

	glBindVertexArray(0);
#pragma region inefficient
	// Vertex Positions
	//glEnableVertexAttribArray(POSITION_LOCATION);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO[VERTICES_BUFFER]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &this->vertices.front(), GL_STATIC_DRAW);
	//glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
	//	(GLvoid*)0);
	
	//// Vertex Normals
	//glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
	//	(GLvoid*)offsetof(Vertex, Normal));
	//glEnableVertexAttribArray(NORMAL_LOCATION);

	//// Vertex Texture Coords
	//glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
	//	(GLvoid*)offsetof(Vertex, TexCoords));
	//glEnableVertexAttribArray(TEX_COORD_LOCATION);

	//// Bone Data
	//glBindBuffer(GL_ARRAY_BUFFER, VBO[BONE_VB]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(Bones[0]) * Bones.size(), &Bones[0], GL_STATIC_DRAW);
	//glVertexAttribIPointer(BONE_ID_LOCATION, 4, GL_INT, sizeof(VertexBoneData), (const GLvoid*)0);
	//glEnableVertexAttribArray(BONE_ID_LOCATION);
	//glVertexAttribPointer(BONE_WEIGHT_LOCATION, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), 
	//	(const GLvoid*)16);
	//glEnableVertexAttribArray(BONE_WEIGHT_LOCATION);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO[MODEL_VB]);
	///*glVertexAttribPointer(MODEL_MAT_LOCATION, 4, GL_FLOAT, GL_FALSE, sizeof(vec4),
	//	(const GLvoid*)0);
	//glEnableVertexAttribArray(MODEL_MAT_LOCATION);
	//glVertexAttribDivisor(MODEL_MAT_LOCATION, 1);
	//*/
	//for (GLuint i = 0; i < 4; i++) 
	//{
	//	glVertexAttribPointer(MODEL_MAT_LOCATION + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), 
	//		(const GLvoid*)(sizeof(vec4) * i));
	//	glEnableVertexAttribArray(MODEL_MAT_LOCATION + i);
	//	glVertexAttribDivisor(MODEL_MAT_LOCATION + i, 1);
	//}
#pragma endregion inefficient

	//glBindVertexArray(0);
	/*vertices.clear();
	indices.clear();*/
}
void Mesh::setupMeshCustom()	
{
	using namespace Stas;

	Vertices_Amount = vertices.size();
	Indices_Amount = indices.size();
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(sizeof(VBO) / sizeof(VBO[0]), this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);
	/*glBindBuffer(GL_ARRAY_BUFFER, this->VBO[);

	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex),
	&this->vertices.front(), GL_STATIC_DRAW);*/
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint),
	&this->indices[0], GL_STATIC_DRAW);*/

	
	glEnableVertexAttribArray(POSITION_LOCATION);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[VERTICES_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &this->vertices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)0);

	// Vertex Normals
	glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(NORMAL_LOCATION);

	// Vertex Texture Coords
	glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(TEX_COORD_LOCATION);

	// Bone Data
	glBindBuffer(GL_ARRAY_BUFFER, VBO[BONE_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Bones[0]) * Bones.size(), &Bones[0], GL_STATIC_DRAW);
	glVertexAttribIPointer(BONE_ID_LOCATION, 4, GL_INT, sizeof(VertexBoneData), (const GLvoid*)0);
	glEnableVertexAttribArray(BONE_ID_LOCATION);
	glVertexAttribPointer(BONE_WEIGHT_LOCATION, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), 
		(const GLvoid*)16);
	glEnableVertexAttribArray(BONE_WEIGHT_LOCATION);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[MODEL_VB]);
	/*glVertexAttribPointer(MODEL_MAT_LOCATION, 4, GL_FLOAT, GL_FALSE, sizeof(vec4),
		(const GLvoid*)0);
	glEnableVertexAttribArray(MODEL_MAT_LOCATION);
	glVertexAttribDivisor(MODEL_MAT_LOCATION, 1);
	*/
	for (GLuint i = 0; i < 4; i++) 
	{
		glVertexAttribPointer(MODEL_MAT_LOCATION + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), 
			(const GLvoid*)(sizeof(vec4) * i));
		glEnableVertexAttribArray(MODEL_MAT_LOCATION + i);
		glVertexAttribDivisor(MODEL_MAT_LOCATION + i, 1);
	}
	glBindVertexArray(0);

}

void Mesh::VertexBoneData::AddBoneData(uint BoneID, float Weight)
{
	for (uint i = 0; i < 2; i++) {
		//if (Weights[i] == 0.0) {
			IDs[i] = BoneID;
			Weights[i] = Weight;
			return;
		//}
	}

	// should never get here - more bones than we have space for
	assert(0);
}

void Mesh::DrawModel()
{
	if (this->scene->HasMaterials())
	{
		unique_ptr<ShaderBuilder> shader = ShaderBuilder::GetCurrentProgram(); 
		shader->Add_Material("material", material);
		for (int i = 0; i < material.NumDiffuse; i++)
		{
			shader->Add_texture("Texture[" + to_string(i) + "]", material.DiffuseTextures[i]);
		}
		for (int i = 0; i < material.NumNormalMap; i++)
		{
			shader->Add_texture("NormalMap[" + to_string(i) + "]", material.NormalMaps[i]);
		}
	}
	vector<aiMatrix4x4> Transforms;
	if (scene->HasAnimations())
	{
		BoneTransform(double(GetTickCount()) / 1000.0f, Transforms);
		unique_ptr<ShaderBuilder> myshader = ShaderBuilder::GetCurrentProgram();
		int BoneNum = Transforms.size();

		myshader->Add_int("BoneNum", BoneNum);
		for (size_t i = 0; i < Transforms.size(); i++)
		{
			myshader->Add_aimat4(string("Bones[") + to_string(i) + string("]"), Transforms[i]);
		}
	}

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, Vertices_Amount);
	glBindVertexArray(0);
}

void Mesh::DrawInstanced(vector<mat4>& ModelMatrix)
{
	if (ModelMatrix.size() == 0)
		return;
	size_t size = sizeof(ModelMatrix[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[MODEL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mat4) * ModelMatrix.size(), &ModelMatrix[0], GL_DYNAMIC_DRAW);


	glBindVertexArray(VAO);
	/*glDrawElementsInstancedBaseVertex(GL_TRIANGLES,
		NumIndices,
		GL_UNSIGNED_INT,
		(void*)(sizeof(unsigned int) * m_Entries[i].BaseIndex),
		Num,
		m_Entries[i].BaseVertex);*/
	glDrawArraysInstanced(GL_POINTS , 0 , Vertices_Amount, ModelMatrix.size());
	glBindVertexArray(0);
}
TODO_FUNCTION Mesh::Material Mesh::LoadMaterial()
{
	auto ConvertAiToGLM = [](aiColor3D color)->vec3 {
		return vec3(color.r, color.g, color.b);
	};

	Mesh::Material material;

	aiColor3D color;
	scene->mMaterials[this->mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_AMBIENT, color);
	material.ambient = ConvertAiToGLM(color);

	scene->mMaterials[this->mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_DIFFUSE, color);
	material.diffuse = ConvertAiToGLM(color);

	float shininess;
	scene->mMaterials[this->mesh->mMaterialIndex]->Get(AI_MATKEY_SHININESS, shininess);
	material.shininess = shininess;

	scene->mMaterials[this->mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_SPECULAR, color);
	material.specular = ConvertAiToGLM(color);

	scene->mMaterials[this->mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_EMISSIVE, color);
	material.emissive = ConvertAiToGLM(color);

	material.NumDiffuse = this->scene->mMaterials[0]->GetTextureCount(aiTextureType::aiTextureType_DIFFUSE);
	material.NumDisplacement = this->scene->mMaterials[0]->GetTextureCount(aiTextureType::aiTextureType_DISPLACEMENT);
	material.NumNormalMap = this->scene->mMaterials[0]->GetTextureCount(aiTextureType::aiTextureType_NORMALS);
	material.NumSpecular = this->scene->mMaterials[0]->GetTextureCount(aiTextureType::aiTextureType_SPECULAR);
	for (int i = 0; i < material.NumDiffuse; i++)
	{
		aiString path;
		string dir = "Collada/";
		this->scene->mMaterials[0]->GetTexture(aiTextureType::aiTextureType_DIFFUSE, i, &path);
		string Path = dir + path.C_Str();
		int textureID = LoadTexture(Path.c_str());
		material.DiffuseTextures.push_back(textureID);
	}
	for (int i = 0; i < material.NumNormalMap; i++)
	{
		aiString path;
		string dir = "Collada/";
		this->scene->mMaterials[0]->GetTexture(aiTextureType::aiTextureType_NORMALS, i, &path);
		string Path = dir + path.C_Str();
		int textureID = LoadTexture(Path.c_str());
		material.NormalMaps.push_back(textureID);
	}
	this->material = material;
	return material;
}
::Material Mesh::GetMaterial()
{
	auto ConvertAiToGLM = [](aiColor3D color)->vec3 {
		return vec3(color.r,color.g,color.b);
	};

	::Material material;

	aiColor3D color;
	scene->mMaterials[this->mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_AMBIENT, color);
	material.ambient = ConvertAiToGLM(color);

	scene->mMaterials[this->mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_DIFFUSE, color);
	material.diffuse = ConvertAiToGLM(color);

	float shininess;
	scene->mMaterials[this->mesh->mMaterialIndex]->Get(AI_MATKEY_SHININESS, shininess);
	material.shininess = shininess;

	scene->mMaterials[this->mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_SPECULAR, color);
	material.specular = ConvertAiToGLM(color);
	
	return material;
}
TODO_FUNCTION void Mesh::GetTextures()
{
	aiString aiPath;
	//int index;
	int count;
	count = this->scene->mMaterials[0]->GetTextureCount(aiTextureType_DIFFUSE);
	for (int i = 0; i < count; i++)
	{
		this->scene->mMaterials[0]->GetTexture(aiTextureType_DIFFUSE, i, &aiPath);
		string path = aiPath.C_Str();
		LoadTexture(path);
	}
	return TODO_FUNCTION void();
}
TODO_FUNCTION void Mesh::GetModelProperties()
{
	/*
	check if file exists
	if date modified newer than model's date, then ok
	else, calculate properties again and write into the file
	*/
	//string Filename = string("/Misc/ModelProperties/") + string("");
	//OFSTRUCT ofstruct;
	//HFILE file = OpenFile("/Misc/ModelProperties/", &ofstruct,0);
	//if (file == 0)
	//FILETIME creationTime,
	//	lpLastAccessTime,
	//	lastWriteTime;
	//bool err = GetFileTime(h, &creationTime, &lpLastAccessTime, &lastWriteTime);
	//if (!err) error
	//return TODO_FUNCTION void();
}
TODO_FUNCTION LOAD_FROM_FILE void Mesh::LoadModelProperties()
{
	FILE* ImportFile;
	nlohmann::json Properties;
	/*this->BB = Properties["BB"];
	this->AABB = Properties["AABB"];
	this->BB.CentralMassPoint = Properties["CentralMassPoint"];*/
}
TODO_FUNCTION LOAD_TO_FILE void Mesh::CalculateModelPropertiesAndSave()
{	
	CreateDirectory("/Misc/ModelProperties", NULL);
	ofstream ExportFile;
	ExportFile.open("/Misc/ModelProperties/" + this->ModelName + to_string(this->MeshCount) + ".data");
	/*this->BB = GetBB();
	this->AABB = GetAABB();*/
	nlohmann::json Properties;
	ExportFile << Properties.dump(1);
	ExportFile.close();
}
void Mesh::ReadNodeHeirarchy(double AnimationTime, const aiNode* pNode, const aiMatrix4x4& ParentTransform)
{
	string NodeName(pNode->mName.data);

	const aiAnimation* pAnimation = scene->mAnimations[0];

	aiMatrix4x4 NodeTransformation(pNode->mTransformation);
	//memcpy(&NodeTransformation, &pNode->mTransformation, 16 * sizeof(float));
	const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);

	if (pNodeAnim) {
		// Interpolate scaling and generate scaling transformation matrix
		aiVector3D Scaling;
		CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
		mat4 ScalingM;
		aiMatrix4x4 ScalingAI;
		ScalingM = glm::scale(ScalingM, vec3(Scaling.x, Scaling.y, Scaling.z));
		ScalingAI.Scaling(Scaling, ScalingAI);

		// Interpolate rotation and generate rotation transformation matrix
		aiQuaternion RotationQ;
		CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
		mat4 RotationM;
		aiMatrix4x4 RotationAI = aiMatrix4x4(RotationQ.GetMatrix());
		RotationAI.Transpose();
		memcpy(&RotationM ,&RotationAI,sizeof(float) * 16);
		//RotationM = glm::rotate(RotationM, (asin(RotationQ.w) /** 180.0f */)/*/ 3.1415f*/, vec3(RotationQ.x,RotationQ.y, RotationQ.z));
		//memcpy(&RotationM, &RotationQ.GetMatrix(), 16 * sizeof(float));

		// Interpolate translation and generate translation transformation matrix
		aiVector3D Translation;
		aiMatrix4x4 TranslationAI;
		CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
		mat4 TranslationM;

		TranslationM = glm::translate(TranslationM, vec3(Translation.x, Translation.y, Translation.z));
		TranslationAI.Translation(Translation, TranslationAI);
		// Combine the above transformations
		mat4 result = TranslationM * RotationM * ScalingM;
		//mat4 result = ScalingM * RotationM * TranslationM;
		//result = glm::transpose(result);
		memcpy(&NodeTransformation, &result, 16 * sizeof(float));
		NodeTransformation.Transpose();
		/*NodeTransformation = TranslationAI * RotationAI * ScalingAI;
		NodeTransformation = ScalingAI * RotationAI * TranslationAI;*/
	}
	//aiMatrix4x4 parent;
	aiMatrix4x4 GlobalTransformation = ParentTransform * NodeTransformation;
	aiMatrix4x4 m_GlobalInverseTransform = scene->mRootNode->mTransformation;
	m_GlobalInverseTransform.Inverse();
	if (m_BoneMapping.find(NodeName) != m_BoneMapping.end()) {
		uint BoneIndex = m_BoneMapping[NodeName];
		m_BoneInfo[BoneIndex].FinalTransformation = m_GlobalInverseTransform * GlobalTransformation *
			/*NodeTransformation*/ m_BoneInfo[BoneIndex].BoneOffset;
	}

	for (uint i = 0; i < pNode->mNumChildren; i++) {
		ReadNodeHeirarchy(AnimationTime, pNode->mChildren[i], GlobalTransformation);
	}
}
uint Mesh::FindPosition(double AnimationTime, const aiNodeAnim* pNodeAnim)
{
	for (uint i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++) {
		if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) {
			return i;
		}
	}

	assert(0);

	return 0;
}

uint Mesh::FindRotation(double AnimationTime, const aiNodeAnim* pNodeAnim)
{
	assert(pNodeAnim->mNumRotationKeys > 0);

	for (uint i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++) {
		if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) {
			return i;
		}
	}

	assert(0);

	return 0;
}


uint Mesh::FindScaling(double AnimationTime, const aiNodeAnim* pNodeAnim)
{
	assert(pNodeAnim->mNumScalingKeys > 0);

	for (uint i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++) {
		if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime) {
			return i;
		}
	}

	assert(0);

	return 0;
}

void Mesh::CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	if (pNodeAnim->mNumPositionKeys == 1) {
		Out = pNodeAnim->mPositionKeys[0].mValue;
		return;
	}

	uint PositionIndex = FindPosition(AnimationTime, pNodeAnim);
	uint NextPositionIndex = (PositionIndex + 1);
	assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
	float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
	float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
	if (Factor <= 0.0f && Factor >= 1.0f)
	{
		Factor = 0.5f;
	}
	const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
	const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
	aiVector3D Delta = End - Start;
	Out = Start + Factor * Delta;
}


void Mesh::CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	// we need at least two values to interpolate...
	if (pNodeAnim->mNumRotationKeys == 1) {
		Out = pNodeAnim->mRotationKeys[0].mValue;
		return;
	}

	uint RotationIndex = FindRotation(AnimationTime, pNodeAnim);
	uint NextRotationIndex = (RotationIndex + 1);
	assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
	float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime);
	float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
	if (Factor <= 0.0f && Factor >= 1.0f)
	{
		Factor = 0.5f;
	}
	const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
	const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
	aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
	Out = Out.Normalize();
}


void Mesh::CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	if (pNodeAnim->mNumScalingKeys == 1) {
		Out = pNodeAnim->mScalingKeys[0].mValue;
		return;
	}

	uint ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
	uint NextScalingIndex = (ScalingIndex + 1);
	assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
	float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
	float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
	if (Factor <= 0.0f && Factor >= 1.0f)
	{
		Factor = 0.5f;
	}
	const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
	const aiVector3D& End = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
	aiVector3D Delta = End - Start;
	Out = Start + Factor * Delta;
}
void Mesh::BoneTransform(double TimeInSeconds, vector<aiMatrix4x4>& Transforms)
{
	aiMatrix4x4 Identity;
	m_NumBones = mesh->mNumBones;
	float TicksPerSecond = (float)(scene->mAnimations[0]->mTicksPerSecond != 0 ? scene->mAnimations[0]->mTicksPerSecond : 25.0f);
	float TimeInTicks = TimeInSeconds * TicksPerSecond;
	float AnimationTime = fmod(TimeInTicks, (float)scene->mAnimations[0]->mDuration);

	ReadNodeHeirarchy(AnimationTime, scene->mRootNode, Identity);

	Transforms.resize(m_NumBones);

	for (uint i = 0; i < m_NumBones; i++) {
		Transforms[i] = m_BoneInfo[i].FinalTransformation;
	}
}
const aiNodeAnim* Mesh::FindNodeAnim(const aiAnimation* pAnimation, const string NodeName)
{
	for (uint i = 0; i < pAnimation->mNumChannels; i++) {
		const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];

		if (string(pNodeAnim->mNodeName.data) == NodeName) {
			return pNodeAnim;
		}
	}

	return NULL;
}
int Mesh::LoadTexture(string Filename)
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
	if (!image)
	{
		string error = SOIL_last_result();
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//	SOIL_free_image_data(image);
	//}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	if (image)
	SOIL_free_image_data(image);
	//glEnable(GL_TEXTURE_2D);
	//unbind texture 2d
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}