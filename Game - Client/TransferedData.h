#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "glm\glm\vec3.hpp"
#include "json.hpp"
#include "Player.h"

using namespace glm;
using namespace std;
using namespace nlohmann;

class TransferedData
{
public:
	TransferedData();
	TransferedData(string);
	~TransferedData();	
	bool UpdateData(string, int);
	bool TranslatedData();
	vector<Player::Unit_Data*> GetUnitData();
	vector<Player::Unit_Data*> Unit;
	unsigned int ClientID = 0;

	void ConvertData(string);
	short static CalculateChecksum(string& Message);
private:
	bool CheckChecksumValidation(string& Message);
	json Data;
};

