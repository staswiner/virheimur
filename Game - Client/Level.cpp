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

	//this->AddEntity(layer, "Mine", EntityType::Entity);
	this->AddEntity(layer, "MineSweaper", EntityType::ActivePlayer);
	this->AddEntity(layer, "Land", EntityType::Ground);
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

void Level::Reset()
{
	this->ClearLevel();
	this->LoadLevel();
}

GameObject* Level::AddEntity(Layer* layer, string Model, EntityType entityType)
{
	GameObject* gameObject = new GameObject();
	gameObject->unit_Data.Model_Data = ModelsCollection::Instance()[Model];
	layer->AddGameObject(gameObject);
	switch (entityType)
	{
	case Level::EntityType::Ground:
		Grounds.push_back(gameObject);
		break;
	case Level::EntityType::ActivePlayer:
		gameObject->unit_Data.HasPhysics = true;
		gameObject->unit_Data.Position = vec3(0,10,0);
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
