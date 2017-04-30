#include "GameObject.h"


GameObject::GameObject()
{
	this->stats.MovementSpeed = 100;
	this->stats.Hp = 500;
	this->stats.MaxHp = 1000;
	LoadInterface(); 
}

GameObject::GameObject(Unit_Data unit_Data,string Username)
{
	this->unit_Data = unit_Data;
	this->stats.MovementSpeed = 100;
	this->stats.Hp = 500;
	this->stats.MaxHp = 1000;
	LoadInterface();
}


GameObject::~GameObject()
{
	UIroot->Destroy();
}

GameObject::Unit_Data& GameObject::GetUnitData()
{
	return this->unit_Data;
}

// TODO : remove projection matrix and view matrix
void GameObject::Draw(SceneData& sceneData)
{
	Mouse& mouse = Mouse::Instanace();

	// Model
	Unit_Data& ud = this->unit_Data;
	vec3 position = ud.Position;
	mat4 ModelMatrix = this->unit_Data.GetModelMatrix();
	mat4 BlenderModelMatrix = ModelMatrix * Default::Instance().BlenderConversion;
	mat4 WVM = sceneData.ProjectionMatrix * sceneData.ViewMatrix * BlenderModelMatrix;
	
	ShaderBuilder::LoadShader(*this->unit_Data.Model_Data->shaderParams.MainShader)->
		Add_mat4("WVM", WVM).
		Add_bool("isAnimated", this->unit_Data.Model_Data->shaderParams.isAnimated).
		Add_mat4("Model", BlenderModelMatrix).
		Add_vec3("lightPos", sceneData.Light_Pos).
		Add_vec3("cameraPos", -sceneData.CameraPos).
		Add_mat4("LightMatrix", sceneData.Light_Matrix);
	this->unit_Data.Model_Data->Draw();
}
void GameObject::DrawShadow(mat4& ProjectionMatrix, mat4& ViewMatrix)
{
	Mouse& mouse = Mouse::Instanace();

	// Model
	Unit_Data& ud = this->unit_Data;
	vec3 position = ud.Position;

#pragma region Mathematics
	mat4 ModelMatrix;
	ModelMatrix = glm::translate(ModelMatrix, position);
	ModelMatrix = glm::rotate(ModelMatrix, ud.Rotation.y, vec3(0, 1, 0));
	mat4 WVM = ProjectionMatrix * ViewMatrix * ModelMatrix* Default::Instance().BlenderConversionCenter;
#pragma endregion Mathematics
	ShaderBuilder::GetCurrentProgram()->
		Add_mat4("WVM", WVM).
		Add_bool("isAnimated", true).
		Add_float("Texelation", 1.0f).
		Add_textures(ModelsCollection::Instance()["Collada"]->Textures);
	ModelsCollection::Instance()["Collada"]->Draw();

}
void GameObject::DrawOutline(mat4& ProjectionMatrix, mat4& ViewMatrix, vec3 Color)
{
	Mouse& mouse = Mouse::Instanace();

	// Model
	Unit_Data& ud = this->unit_Data;
	vec3 position = ud.Position;
#pragma region Mathematics
	mat4 ModelMatrix;
	ModelMatrix = glm::translate(ModelMatrix, position);
	ModelMatrix = glm::rotate(ModelMatrix, ud.Rotation.y, vec3(0, 1, 0));
	ModelMatrix = glm::scale(ModelMatrix, vec3(1.03f));
	mat4 WVM = ProjectionMatrix * ViewMatrix * ModelMatrix * Default::Instance().BlenderConversionCenter;
#pragma endregion Mathematics
	ShaderBuilder::LoadShader(Shader::At("Color"))->
		Add_mat4("WVM", WVM).
		Add_bool("isAnimated", false).
		Add_vec3("Color", Color);
	ModelsCollection::Instance()["Collada"]->Draw();

}

void GameObject::DrawUI(mat4 & ProjectionMatrix, mat4 & ViewMatrix)
{
#pragma region Declarations
	Mouse& mouse = Mouse::Instanace();

	mat4 ModelMatrix;
	Unit_Data& ud = this->unit_Data;
	vec3 position = ud.Position;
#pragma endregion Declarations
	ModelMatrix = glm::translate(ModelMatrix, position);
	ModelMatrix = glm::rotate(ModelMatrix, ud.Rotation.y, vec3(0, 1, 0));
	mat4 WVM = ProjectionMatrix * ViewMatrix * ModelMatrix;
	// HP bar
	float x = mouse.GetWindowSize().x / 2.0f;
	float y = mouse.GetWindowSize().y / 2.0f;
	vec4 TextPosition = WVM * vec4(0, 0, 0, 1);
	TextPosition /= TextPosition.w;
	vec2 TextCoords = vec2(TextPosition.x * x + x, -TextPosition.y * y + y);
	UIElement* EmptyHPBar = UIroot->GetUIElement("EmptyHPBar");
	UIElement* FullHPBar = UIroot->GetUIElement("FullHPBar");
	EmptyHPBar->TopLeft = TextCoords + vec2(-30, -30);
	EmptyHPBar->SetByTrueSize();

	FullHPBar->TopLeft = TextCoords + vec2(-29, -29);
	FullHPBar->BotRight = vec2(FullHPBar->TopLeft.x + (this->stats.Hp)/float(this->stats.MaxHp)*FullHPBar->TrueSize.x
		,FullHPBar->TopLeft.y+FullHPBar->TrueSize.y);

	UIroot->Draw();

}

void GameObject::LoadInterface()
{
	vec2 Position;
	UIroot = new UIElement("Root", "");

	UIElement* EmptyHPBar = new UIElement("EmptyHPBar", "Interface/EmptyHPBar.png");
	Position = vec2(10, 80);
	EmptyHPBar->TopLeft = Position;
	EmptyHPBar->SetByTrueSize(Position);
	UIroot->AppendChild(EmptyHPBar);

	UIElement* FullHPBar = new UIElement("FullHPBar", "Interface/FullHPBar.png");
	Position = vec2(10, 80);
	FullHPBar->TopLeft = Position;
	FullHPBar->SetByTrueSize(Position);
	UIroot->AppendChild(FullHPBar);


}

void GameObject::UpdateUnitData(Unit_Data uData)
{
	this->unit_Data.Destination = uData.Position;
}

void GameObject::ReloadShader()
{
	if (this->unit_Data.Model_Data)
	{
		this->unit_Data.Model_Data->ReloadShader();
	}
}

void GameObject::ReloadShader(Shader::ImageType imageType)
{
	if (this->unit_Data.Model_Data)
	{
		this->unit_Data.Model_Data->ReloadShader(imageType);
	}
}

json GameObject::GetJson()
{
	json JPlayer;
	JPlayer["x"] = this->unit_Data.StartPoint.x;
	JPlayer["y"] = this->unit_Data.StartPoint.y;
	JPlayer["z"] = this->unit_Data.StartPoint.z;
	JPlayer["Destx"] = this->unit_Data.Destination.x;
	JPlayer["Desty"] = this->unit_Data.Destination.y;
	JPlayer["Destz"] = this->unit_Data.Destination.z;
	for (uint i = 0; i < this->unit_Data.Path.size(); i++)
	{
		JPlayer["Path"][i]["x"] = this->unit_Data.Path[i].x;
		JPlayer["Path"][i]["y"] = this->unit_Data.Path[i].y;
		JPlayer["Path"][i]["z"] = this->unit_Data.Path[i].z;
	}
	//JPlayer["Path"] = this->unit_Data.Path;
	//JPlayer["Hp"] = this->stats.Hp;
	//JPlayer["MaxHp"] = this->stats.MaxHp;
	JPlayer["StartTime"] = this->unit_Data.StartPointTime.count();
	JPlayer["IpAddress"] = this->IpAddress;
	//JPlayer["Username"] = this->Username;
	return JPlayer;
}

//	void* SetMemoryData(string VarName);
//void SetMemoryData(string VarName, string VarType, void* data);
//
//map<string, void*> MemoryBlock;
//map<string, string> MemoryTypeTable;
#define StringToType(string) ()
void * GameObject::GetMemoryData(string VarName)
{
	// TODO:
	if (MemoryBlock.find(VarName) == MemoryBlock.end())
	{
		return nullptr;
	}
	else
	{
		float number = *reinterpret_cast<float*>(MemoryBlock[VarName]);
		return MemoryBlock[VarName];
	}
}

void GameObject::SetMemoryData(string VarName, void * data, size_t s)
{
	//TODO:	
	
	float number = *reinterpret_cast<float*>(data);
	void * AllocationData = malloc(sizeof(s));
	memcpy(AllocationData, data, s);
	number = *reinterpret_cast<float*>(AllocationData);
	void * ptr = MemoryBlock[VarName];
	if (MemoryBlock.find(VarName) != MemoryBlock.end())
	{

		//float number = *reinterpret_cast<float*>(MemoryBlock[VarName]);
		MemoryBlock.erase(VarName);
	}
	MemoryBlock[VarName] = AllocationData;
}

void GameObject::CreateCollisionBody(rp3d::CollisionWorld& world)
{
	rp3d::Vector3 position;
	position.x = this->unit_Data.Position.x;
	position.y = this->unit_Data.Position.y;
	position.z = this->unit_Data.Position.z;
	rp3d::Quaternion orientation = rp3d::Quaternion::identity();
	rp3d::Transform transform(position, orientation);
	this->collisionBody = world.createCollisionBody(transform);
}

void GameObject::UpdateCollisionBody(rp3d::CollisionWorld& world)
{
	rp3d::Vector3 position;
	position.x = this->unit_Data.Position.x;
	position.y = this->unit_Data.Position.y;
	position.z = this->unit_Data.Position.z;
	rp3d::Quaternion orientation = rp3d::Quaternion::identity();
	rp3d::Transform transform(position, orientation);
	this->collisionBody->setTransform(transform);
}

GameObject *& PlayerRepository::operator[](string Key)
{
	if (this->Players.find(Key) == this->Players.end())
	{
		this->Players[Key] = new GameObject();
		return this->Players[Key];
	}
	else
	{
		return this->Players[Key];
	}
}

GameObject * PlayerRepository::operator[](string Key) const
{
	if (this->Players.find(Key) == this->Players.end())
	{
		this->Players[Key] = new GameObject();
		return this->Players[Key];
	}
	else
	{
		return this->Players[Key];
	}
}

void PlayerRepository::Erase(string Key)
{
	this->Players.erase(Key);
}

map<string, GameObject*>::iterator PlayerRepository::begin()
{
	return this->Players.begin();
}

map<string, GameObject*>::iterator PlayerRepository::end()
{
	return this->Players.end();
}

void PlayerRepository::clear()
{
	for (auto p : Players)
	{
		delete p.second;
	}
	Players.clear();
}

GameObject::Unit_Data::Unit_Data()
{
}

GameObject::Unit_Data::~Unit_Data()
{
	Path.clear();
	if (Model_Data)
	{
		delete Model_Data;
	}
}
mat4 GameObject::Unit_Data::GetModelMatrix()
{
	mat4 ModelMatrix;
	quat Quaternion(this->Rotation);
	ModelMatrix = glm::translate(ModelMatrix, this->Position);
	mat4 RotationMat = (mat4)Quaternion;
	ModelMatrix = ModelMatrix * (mat4)Quaternion;
	
	return ModelMatrix;
}

void GameObject::Unit_Data::RotateByNormal(vec3 NormalAngles)
{
	//mat4 ModelMatrix;
	//quat Quaternion(this->Rotation);
	//ModelMatrix = glm::translate(ModelMatrix, this->Position);
	//mat4 RotationMat = (mat4)Quaternion;
	//ModelMatrix = ModelMatrix * (mat4)Quaternion;
	this->SurfaceNormal = NormalAngles;
}

void Effect2D::Draw(SceneData & sceneData)
{
}
