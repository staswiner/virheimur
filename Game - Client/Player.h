#pragma once
#include "Unit_Data.h"
#include "json.hpp"
using namespace nlohmann;
class Player
{
public:
	Player() {}
	Player(Unit_Data,string Username,string IpAddress = "255.255.255.255",int Type=0);
	~Player();
	Unit_Data& GetUnitData();
	void UpdateUnitData(Unit_Data uData);
	json GetJson();
	int GetType();
	string GetIP() { return this->IpAddress; }
	string GetUsername() { return this->Username; }
	string Username;
	struct Stats{
		uint Exp;
		uint Hp;
		uint Mp;
		uint MovementSpeed;

	};
	Stats stats;
	milliseconds TimeDelta;
	Unit_Data unit_Data;
private:
	string IpAddress;
	int Type;
};

