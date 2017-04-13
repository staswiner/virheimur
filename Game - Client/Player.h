#pragma once
#include "json.hpp"
#include "UIElement.h"
#include "FrameData.h"
#include <functional>
#include "glm\glm\vec3.hpp"
#include "Model.h"
#include "Loaded_Models.h"
#include "Default.h"
#include <chrono>

using namespace chrono;
using namespace glm;

using namespace std;
using namespace nlohmann;

class Player
{
public:
	struct Stats{
		uint Level;
		uint Exp;
		uint MaxHp;
		uint Hp;
		uint Mp;
		uint MovementSpeed = 10;
		uint Gold;
	};

	class Unit_Data
	{
	public:
		Unit_Data();
		~Unit_Data();
		mat4 GetModelMatrix();
		Model* GetModelData() const;
		// When destination is chosen, StartPointTime is updated with the action time. 
		// Later Calculates the route based on this factor and walking speed
	public:
		vec3 StartPoint;
		vec3 Position;
		vec3 Rotation;
		vector<vec3> Path;
		vec3 Destination;
		bool PathChanged = false;
		milliseconds StartPointTime;
		Model* Model_Data;
		unsigned int action;
	};

	Player();
	Player(Unit_Data, string Username);
	~Player();
	Unit_Data& GetUnitData();
	void Draw();
	void DrawShadow(mat4 & ProjectionMatrix, mat4 & ViewMatrix);
	void DrawOutline(mat4 & ProjectionMatrix, mat4 & ViewMatrix, vec3 Color);
	void DrawUI(mat4& Projection, mat4& View);
	void LoadInterface();
	void UpdateUnitData(Unit_Data uData);
	json GetJson();
	json GetStructureJson();
	int GetType();
	string GetIP() { return this->IpAddress; }
	string GetUsername() { return this->Username; }
	string Username;
	string CharacterName;
	struct Coordinations {
	};

	Stats stats;
	milliseconds TimeDelta;
	Unit_Data unit_Data;
	// Controls
	enum class controls
	{
		Manual,
		Direct,
		Script,
		Mouse
	}; 
	enum class movements
	{
		Ground,
		Plane, 
		Aero
	};
	movements movement = movements::Ground;
	controls control = controls::Manual;
	// AI preparations
	function<void(Player&)> script;
	void* GetMemoryData(string VarName);
	void SetMemoryData(string VarName, void* data, size_t);
	bool disablePathing = false;
	// TO remove variable
	bool PathingStarted = false;
	bool LongPath = true;

private:
	map<string, void*> MemoryBlock;
	map<string, string> MemoryTypeTable;
	string IpAddress;
	UIElement* UIroot;
	int Type;
};

typedef Player::Unit_Data Unit_Data;

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