#pragma once
#include "Layer.h"
#include "File.h"
#include "json.hpp"
using namespace nlohmann;
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
	void Reset();

	vector<GameObject*> Grounds;
	vector<GameObject*> ActivePlayers;
	vector<GameObject*> PassivePlayers;
	vector<GameObject*> Entities;
	vector<GameObject*> GameObjects;
private:
	GameObject* AddEntity(Layer* layer, string Model, EntityType, vec3 Position = vec3());
	Layers layers;
	void LoadJsonData(string path);
	void ClearLevel();

};

