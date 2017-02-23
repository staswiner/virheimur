#pragma once
#include "Unit_Data.h"
#include "json.hpp"
#include "UIElement.h"
using namespace nlohmann;
class Player
{
public:
	Player();
	Player(Unit_Data, string Username);
	~Player();
	Unit_Data& GetUnitData();
	void Draw(mat4& Projection, mat4& View);
	void DrawShadow(mat4 & ProjectionMatrix, mat4 & ViewMatrix);
	void DrawOutline(mat4 & ProjectionMatrix, mat4 & ViewMatrix, vec3 Color);
	void DrawUI(mat4& Projection, mat4& View);
	void LoadInterface();
	void UpdateUnitData(Unit_Data uData);
	json GetJson();
	int GetType();
	string GetIP() { return this->IpAddress; }
	string GetUsername() { return this->Username; }
	string Username;
	string CharacterName;
	struct Stats{
		uint Level;
		uint Exp;
		uint MaxHp;
		uint Hp;
		uint Mp;
		uint MovementSpeed;
		uint Gold;

	};
	Stats stats;
	milliseconds TimeDelta;
	Unit_Data unit_Data;
private:
	string IpAddress;
	UIElement* UIroot;
	int Type;
};

class PlayerRepository
{
public:
	PlayerRepository() {}
	~PlayerRepository() { Players.clear(); }
	Player*& operator[](string Key);
	Player* operator[](string Key) const;
	void Erase(string Key);
	map<string, Player*>::iterator begin();
	map<string, Player*>::iterator end();
	void clear();
private:
	mutable map<string, Player*> Players;
};