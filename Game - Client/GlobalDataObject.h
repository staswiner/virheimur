#pragma once
#include "json.hpp"
#include "Player.h"
#include <string>
#include <vector>
using namespace std;
using namespace nlohmann;

class GlobalDataObject
{
public:
	GlobalDataObject();
	~GlobalDataObject();
	void TestInit();
	void ReceiveDataString(string);
	void UpdateMyPlayer(Player, string Username);
	void SetMyIP(string myIP) { MyIP = myIP; }
	string GetMyIP() { return MyIP; }
	map<string,Player>& GetPlayerInformation();

	string MyUsername;
	map<vec3, map<vec3, int, bool(*)(const vec3&, const vec3&)>
		, bool(*)(const vec3&, const vec3&)>* Map;
	vector<vec3>* Path;
	bool RouteChanged = false;

private:
	json Data;
	map<string,Player> Players;
	string MyIP;
};
typedef GlobalDataObject GDO;
