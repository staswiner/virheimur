#include "Mesh.h"


Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}
Mesh::Mesh(aiMesh * mesh, const aiScene* scene)
{
	this->mesh = mesh;
	this->scene = scene;
	ProcessMesh();
}
void Mesh::ProcessMesh()
{

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
		mesh;
	}
	// Textures
	m_Texture.push_back(LoadTexture("Collada/Katarina Glowing.bmp"));
	m_Texture.push_back(LoadTexture("Collada/Tex/head01.png"));

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
	for (int i = 0; i < scene->mNumAnimations; i++)
	{
		Animations.push_back(scene->mAnimations[i]);
	}
	this->setupMesh();
}
void Mesh::setupMesh()
{
	Vertices_Amount = vertices.size();
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

	// Vertex Positions
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
	//glBufferData(GL_ARRAY_BUFFER, sizeof(mat4)*150, NULL, GL_DYNAMIC_DRAW);
	for (GLuint i = 0; i < 4; i++) 
	{
		glEnableVertexAttribArray(MODEL_MAT_LOCATION + i);
		glVertexAttribPointer(MODEL_MAT_LOCATION, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (const GLvoid*)(sizeof(GLfloat) * i * 4));
		glVertexAttribDivisor(MODEL_MAT_LOCATION + i, 1);
	}

	glBindVertexArray(0);
	/*vertices.clear();
	indices.clear();*/
}
void Mesh::loadMesh()
{

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
void Mesh::Draw(Shader shader)
{
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	for (GLuint i = 0; i < this->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // Activate proper texture unit before binding
										  // Retrieve texture number (the N in diffuse_textureN)
		stringstream ss;
		string number;
		string name = this->textures[i].type;
		if (name == "texture_diffuse")
			ss << diffuseNr++; // Transfer GLuint to stream
		else if (name == "texture_specular")
			ss << specularNr++; // Transfer GLuint to stream
		number = ss.str();

		glUniform1i(glGetUniformLocation(shader.ProgramID, ("material." + name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	shader.Use();
	Mouse mouse;
	mat4 ModelMat;
	mat4 ViewMat;
	mat4 PerspectiveMat = glm::perspective(radians(120.0f),
		float(mouse.GetWindowSize().x / mouse.GetWindowSize().y), 1.0f, 1000.0f);
	GLint modelID = glGetUniformLocation(shader.ProgramID, "model");
	GLint viewID = glGetUniformLocation(shader.ProgramID, "view");
	GLint projectionID = glGetUniformLocation(shader.ProgramID, "projection");
	glUniformMatrix4fv(modelID, 1, GL_FALSE, value_ptr(ModelMat));
	glUniformMatrix4fv(viewID, 1, GL_FALSE, value_ptr(ViewMat));
	glUniformMatrix4fv(projectionID, 1, GL_FALSE, value_ptr(PerspectiveMat));

	// Draw mesh
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
	glBindVertexArray(0);
	/*glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);*/
}
void Mesh::DrawModel()
{
	vector<aiMatrix4x4> Transforms;
	if (scene->HasAnimations())
	{
		BoneTransform(float(GetTickCount()) / 1000.0f, Transforms);
	}
	ShaderBuilder myshader = *ShaderBuilder::LoadShader(Shader::At("Animation"));
	for (int i = 0; i < m_Texture.size(); i++)
	{
		myshader.Add_texture("myTexture"+i, m_Texture[i]);
	}

	for (int i = 0; i < Transforms.size(); i++)
	{
		myshader.Add_aimat4(string("Bones[") + to_string(i) + string("]"), Transforms[i]);
	}
	mat4 test;
	test = glm::scale(test, vec3(2, 2, 2));
	myshader.Add_mat4(string("Bones[") + to_string(0) + string("]"), test);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, Vertices_Amount);
	glBindVertexArray(0);
}
void Mesh::DrawInstanced(int Num, vector<mat4>& ModelMatrix)
{
	Num = 100;
	int a = sizeof(mat4);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[MODEL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mat4) * Num, &(ModelMatrix[0]), GL_DYNAMIC_DRAW);


	glBindVertexArray(VAO);
	/*glDrawElementsInstancedBaseVertex(GL_TRIANGLES,
		NumIndices,
		GL_UNSIGNED_INT,
		(void*)(sizeof(unsigned int) * m_Entries[i].BaseIndex),
		Num,
		m_Entries[i].BaseVertex);*/
	glEnableVertexAttribArray(0);
	glDrawArraysInstanced(GL_TRIANGLES , 0 , Num*Vertices_Amount,Num);
	glBindVertexArray(0);
}
void Mesh::ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const aiMatrix4x4& ParentTransform)
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
uint Mesh::FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	for (uint i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++) {
		if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) {
			return i;
		}
	}

	assert(0);

	return 0;
}

uint Mesh::FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
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


uint Mesh::FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim)
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
void Mesh::BoneTransform(float TimeInSeconds, vector<aiMatrix4x4>& Transforms)
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