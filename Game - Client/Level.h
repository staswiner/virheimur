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
	void Draw();
	vector<GameObject*> Grounds;
	vector<GameObject*> ActivePlayers;
	vector<GameObject*> PassivePlayers;
	vector<GameObject*> Entities;
private:
	GameObject* AddEntity(Layer* layer, string Model, EntityType);
	Layers layers;

};

