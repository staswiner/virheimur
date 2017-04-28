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

	this->AddEntity(layer, "Mine", EntityType::Entity);
	this->AddEntity(layer, "MineSweaper", EntityType::ActivePlayer);
	this->AddEntity(layer, "Land", EntityType::Ground);
	this->AddEntity(layer, "Mine", EntityType::Entity);

	layers.Add(layer, LayerType::FinalObject);
}

void Level::ReloadShaders()
{
	layers.ReloadShaders();
}

void Level::Draw()
{
	layers.Draw();
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
		ActivePlayers.push_back(gameObject);
		break;
	case Level::EntityType::PassivePlayer:
		PassivePlayers.push_back(gameObject);
		break;
	case Level::EntityType::Entity:
		Entities.push_back(gameObject);
		break;
	default:
		break;
	}
	return gameObject;


}
