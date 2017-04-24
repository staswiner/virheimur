#pragma once
#include "json.hpp"
#include "Player.h"
#include "Effect.h"
#include "AIObjects.h"
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
	map<vec3, map<vec3, float, bool(*)(const vec3&, const vec3&)>
		, bool(*)(const vec3&, const vec3&)>* Graph;
	vector<vec3>* Path;
	bool RouteChanged = false;

	// Normal Map Heights should be in data, sent to Map to draw
	Stas::MinimapData Map;
	vector<Effect> Effects;
	vector<string> Highlight;

private:
	json Data;
	PlayerRepository& Players;
	vector<AIObjects> Monsters;
	PlayerRepository NewPlayers;
	string MyIP;
};

typedef GlobalDataObject GDO;

class OfflineDataObject
{
private:
	OfflineDataObject() {
		
	}
	OfflineDataObject(OfflineDataObject const&) = delete;
	void operator=(OfflineDataObject const&) = delete;

	static OfflineDataObject instance;

public:
	~OfflineDataObject() {}
	static OfflineDataObject& Instance()
	{
		static OfflineDataObject instance;
		return instance;
	}

	GameObject player;
	vector<Effect> Effects;
	vector<vec3>* Path;
	bool RouteChanged = false;
};