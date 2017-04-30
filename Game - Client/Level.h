#pragma once
#include "Layer.h"
class Level
{
public:
	enum class EntityType {
		Ground,
		ActivePlayer,
		PassivePlayer,
		Entity
	};
	Level();
	~Level();
	void LoadLevel();
	void ReloadShaders();
	void ReloadShaders(Shader::ImageType);
	void Draw();

	vector<GameObject*> Grounds;
	vector<GameObject*> ActivePlayers;
	vector<GameObject*> PassivePlayers;
	vector<GameObject*> Entities;
	vector<GameObject*> GameObjects;
private:
	GameObject* AddEntity(Layer* layer, string Model, EntityType);
	Layers layers;

};

