#include "Level.h"



Level::Level()
{
	
}


Level::~Level()
{
}

void Level::LoadLevel()
{
	Layer* layer = new Layer();

	GameObject* gameObject = new SkyBox();
	dynamic_cast<SkyBox*>(gameObject)->Initialize();
	layer->AddGameObject(gameObject);

	this->LoadJsonData("Level1.ld", layer);
	//this->AddEntity(layer, "Mine", EntityType::Entity);
	//for (int i = 0; i < 1; i++)
	//{
	//	for (int j = 0; j < 1; j++)
	//	{
	//		this->AddEntity(layer, "MineSweaper", EntityType::ActivePlayer, vec3(2*i, 10, 2*j));
	//	}
	//}
	//this->AddEntity(layer, "MineSweaper", EntityType::ActivePlayer, vec3(0,0,0));
	//this->AddEntity(layer, "Land", EntityType::Ground);
	gameObject = new Effect2D("Interface/3D Effects/Sun.png"); /*this->AddEntity(layer, "Mine", EntityType::Entity);*/
	gameObject->unit_Data.Position = FrameData::Instance().Light_Pos;
	layer->AddGameObject(gameObject);

	layers.Add(layer, LayerType::FinalObject);
}

void Level::ReloadShaders()
{
	layers.ReloadShaders();
}

void Level::ReloadShaders(Shader::ImageType imageType)
{
	layers.ReloadShaders(imageType);
}

void Level::Draw()
{
	layers.Draw();
}

void Level::Update()
{
	layers.Update();
}

void Level::Reset()
{
	this->ClearLevel();
	this->LoadLevel();
}

GameObject* Level::AddEntity(Layer* layer, string Model, EntityType entityType, vec3 Position)
{
	GameObject* gameObject = new SimpleObject();
	gameObject->unit_Data.Model_Data = ModelsCollection::Instance()[Model];
	layer->AddGameObject(gameObject);
	switch (entityType)
	{
	case Level::EntityType::Ground:
		Grounds.push_back(gameObject);
		break;
	case Level::EntityType::ActivePlayer:
		gameObject->unit_Data.HasPhysics = true;
		gameObject->unit_Data.Position = Position;
		ActivePlayers.push_back(gameObject);
		break;
	case Level::EntityType::PassivePlayer:
		PassivePlayers.push_back(gameObject);
		break;
	case Level::EntityType::Entity:
		gameObject->unit_Data.HasPhysics = true;
		Entities.push_back(gameObject);
		break;
	default:
		break;
	}
	this->GameObjects.push_back(gameObject);
	return gameObject;


}

void Level::LoadJsonData(string path, Layer* layer)
{
	string sData = Stas::File::Read(path);
	json jData = json::parse(sData.c_str());
	for (int i = 0; i < jData.size(); i++)
	{
		string Name = jData[i]["Name"];
		string Type = jData[i]["Type"];
		string CollisionType = jData[i]["CollisionType"];
		string PositionStr = jData[i]["Position"];
		json Positions = json::parse(PositionStr.c_str());
		float x = Positions["x"];
		float y = Positions["y"];
		float z = Positions["z"];
		string Model = jData[i]["Model"];
		EntityType entityType;
		if (Type == "Ground") entityType = EntityType::Ground;
		if (Type == "ActivePlayer") entityType = EntityType::ActivePlayer;
		if (Type == "PassivePlayer") entityType = EntityType::PassivePlayer;
		if (Type == "Entity") entityType = EntityType::Entity;
		
//#define IntToEnum(Enum,i) static_cast<Enum>(i);
//#define Loop(Enum) \
//		for (int i = 0; i < static_cast<int>(Enum::End); i++) \
//		{ \
//			if (Type==#Enum) { entityType = IntToEnum(Enum,i); break;} \
//		} /**/
//		Loop(EntityType);

		this->AddEntity(layer, Model, entityType, vec3(x,y,z));
	}
}

void Level::ClearLevel()
{
	this->layers.Clear();
	for (auto g : GameObjects) delete g;

	Grounds.clear();
	ActivePlayers.clear();
	PassivePlayers.clear();
	Entities.clear();
	GameObjects.clear();
}
