#pragma once
#include "Layer.h"
#include "File.h"
#include "json.hpp"
#include <memory>
using namespace nlohmann;
class Level
{
public:
	enum class EntityType {
		Ground,
		ActivePlayer,
		PassivePlayer,
		Entity,
		End
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
	Layers layers;
private:
	GameObject* AddEntity(Layer* layer, string Model, EntityType, vec3 Position = vec3());
	void LoadJsonData(string path, Layer* layer);
	void ClearLevel();

};

