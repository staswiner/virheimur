#pragma once
#include "json.hpp"
#include "Player.h"
#include "Effect.h"
#include <string>
#include <vector>
using namespace std;
using namespace nlohmann;

class GlobalDataObject
{
public:
	GlobalDataObject(): Players(this->NewPlayers){}
	GlobalDataObject(PlayerRepository& Players); // default constructor
	GlobalDataObject(const GlobalDataObject&); // copy constructor
	~GlobalDataObject();
	GlobalDataObject& operator=(const GlobalDataObject& rhs);
	void Clear();
	void TestInit();
	void ReceiveDataString(string);
	void SetMyIP(string myIP) { MyIP = myIP; }
	string GetMyIP() { return MyIP; }
	PlayerRepository& GetPlayerInformation();

	string MyUsername;
	map<vec3, map<vec3, int, bool(*)(const vec3&, const vec3&)>
		, bool(*)(const vec3&, const vec3&)>* Map;
	vector<vec3>* Path;
	bool RouteChanged = false;

	vector<Effect> Effects;
private:
	json Data;
	PlayerRepository& Players;
	PlayerRepository NewPlayers;
	string MyIP;
};
typedef GlobalDataObject GDO;
