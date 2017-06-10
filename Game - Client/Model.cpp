#include "Model.h"

Model::Model()
{
}

Model::Model(GLchar* Path, string CollisionType)
{
	this->CollisionType = CollisionType;
	this->loadModel(Path);
}
Model::Model(Mesh& mesh)
{
	this->loadModel(mesh);
}

Model::~Model()
{
	meshes.clear();
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
	/*vector<Stas::Vertex> vertices;
	vector<GLuint> indices;
	vector<Mesh::Texture> textures;*/

	return Mesh(mesh,scene, CollisionType);
}

void Model::loadModel(Mesh& mesh)
{
	this->meshes.push_back(mesh);
}
vector<Mesh::Texture> Model::loadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName)
{
	return vector<Mesh::Texture>();
}
void Model::loadModel(string Path)
{
	int pos = Path.find_last_of('/');
	this->ModelName = Path.substr(pos + 1, Path.length());
	scene = import.ReadFile(Path,
		//aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		//	aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType 
		//aiProcess_ImproveCacheLocality
		);

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

	//
	this->CreateShader();
// 	delete scene;
}

void Model::Draw()
{
	//ShaderBuilder::GetCurrentProgram()->

	for (GLuint i = 0; i < this->meshes.size(); i++)
		this->meshes[i].DrawModel();
}
void Model::DrawInstanced(vector<mat4>& ModelMatrix)
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

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);// (GL_UNPACK_ALIGNMENT, 3); ​
	image = SOIL_load_image(Filename.c_str(), &Width, &Height, 0, SOIL_LOAD_AUTO);
	const char* error = SOIL_last_result();
	if (Filename.find(".png") != -1)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	else
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

void Model::AddTexture(string TextureName,string Filename)
{
	this->Textures[TextureName]=this->LoadTexture(Filename);
}

vector<vector<int>> Model::LoadBufferFromImage(string Filename)
{
	GLuint texture;
	vector<vector<int>> Data;
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
	Data.resize(Height);
	for (auto& d : Data)
	{
		d.resize(Width);
	}
	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			Data[i][j] = image[i*Width + j];
		}
	}
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
	return Data;
}
void Model::CreateShader() // TODO : should be moved to mesh
{
	Shader::ShaderInfo shaderInfo;
	shaderInfo.HasMaterial = this->scene->HasMaterials();
	shaderInfo.NumDiffuse = this->scene->mMaterials[0]->GetTextureCount(aiTextureType::aiTextureType_DIFFUSE);
	shaderInfo.NumDisplacement = this->scene->mMaterials[0]->GetTextureCount(aiTextureType::aiTextureType_DISPLACEMENT);
	shaderInfo.NumNormalMap = this->scene->mMaterials[0]->GetTextureCount(aiTextureType::aiTextureType_NORMALS);
	shaderInfo.NumSpecular = this->scene->mMaterials[0]->GetTextureCount(aiTextureType::aiTextureType_SPECULAR);
	//for (int i = 0; i < shaderInfo.NumDiffuse; i++)
	//{
	//	aiString path;
	//	LoadTexture(this->scene->mMaterials[0]->GetTexture(aiTextureType::aiTextureType_DIFFUSE,i,))
	//	shaderInfo.DiffuseTextures.push_back(Load)
	//}
	this->shaderParams.MainShader = Shader::ConstructShader(shaderInfo);
}
Shader* Model::CreateShader(Shader::ImageType imageType)
{
	Shader::ShaderInfo shaderInfo;
	shaderInfo.HasMaterial = this->scene->HasMaterials();
	shaderInfo.NumDiffuse = this->scene->mMaterials[0]->GetTextureCount(aiTextureType::aiTextureType_DIFFUSE);
	shaderInfo.NumDisplacement = this->scene->mMaterials[0]->GetTextureCount(aiTextureType::aiTextureType_DISPLACEMENT);
	shaderInfo.NumNormalMap = this->scene->mMaterials[0]->GetTextureCount(aiTextureType::aiTextureType_NORMALS);
	shaderInfo.NumSpecular = this->scene->mMaterials[0]->GetTextureCount(aiTextureType::aiTextureType_SPECULAR);
	shaderInfo.imageType = imageType;
	//for (int i = 0; i < shaderInfo.NumDiffuse; i++)
	//{
	//	aiString path;
	//	LoadTexture(this->scene->mMaterials[0]->GetTexture(aiTextureType::aiTextureType_DIFFUSE,i,))
	//	shaderInfo.DiffuseTextures.push_back(Load)
	//}
	return Shader::ConstructShader(shaderInfo);
}
void Model::ReloadShader()
{
	if (this->shaderParams.MainShader)
	{
		delete this->shaderParams.MainShader;
		this->CreateShader();
	}
}

void Model::ReloadShader(Shader::ImageType imageType)
{
	if (this->shaderParams.MainShader)
	{
		delete this->shaderParams.MainShader;
		this->CreateShader(imageType);
	}
}

Models2D::Models2D()
{
}

Models2D::~Models2D()
{
}

Models2D::Models2D(GLchar * path)
{
	this->LoadTexture(path);
}

void Models2D::Draw3DFacingCamera(vec3 WorldSpace)
{
	mat4 WorldPos = glm::translate(mat4(), WorldSpace);
	mat4& ViewMatrix = Camera::GetCamera(Camera::eCamera::Current).ViewMatrix;
	mat4& ProjectionMatrix = Camera::GetCamera(Camera::eCamera::Current).ProjectionMatrix;
	Mouse& mouse = Mouse::Instanace();

	glm::mat4 projectionOrtho = glm::ortho(0.0f, mouse.GetWindowSize().x,
		mouse.GetWindowSize().y, 0.0f);
	vec4 ClipPosition = ProjectionMatrix * ViewMatrix * WorldPos * vec4(0, 0, 0, 1);
	ClipPosition /= ClipPosition.w;
	if (ClipPosition.z > 1) return;
	float x = mouse.GetWindowSize().x / 2.0f;
	float y = mouse.GetWindowSize().y / 2.0f;

	vec2 ClipCoords = vec2(ClipPosition.x * x + x, -ClipPosition.y * y + y);
	//ShaderBuilder::LoadShader(shader)->Add_mat4("projection", projection).
	//	Add_mat4("view", view);// .Add_mat4("model", model);// .Add_mat4("worldPos", WorldPos);

	/*Frame*/
	// TODO
	//
	//
	//ChatFrames[0]->DrawImagePart(vec2(0, 0), vec2(300, 300), vec2(300, 300),
	//	vec2(0, 0), vec2(300, 300));

	/*Text*/
	ShaderBuilder::LoadShader(Shader::At("3D Image"))->
		Add_mat4("projection", projectionOrtho).
		Add_mat4("view", mat4()).
		Add_mat4("model", mat4()).
		Add_texture("ourTexture", 0);
	//this->image->Draw();
}

int Models2D::LoadTexture(string Filename)
{
	image = new ImageLoader();
	image->Initialize(Filename);
	this->TrueSize = image->GetTrueSize(); 
	return 0;
}
