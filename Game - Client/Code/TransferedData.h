#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "glm\glm\vec3.hpp"
#include "Unit_Data.h"
#include "json.hpp"

using namespace glm;
using namespace std;
using namespace nlohmann;
class Data {
public: Data() {}
		~Data() {}
};
class TransferedData
{
public:
	TransferedData();
	TransferedData(string);
	~TransferedData();	
	bool UpdateData(string, int);
	bool TranslatedData();
	vector<Unit_Data*> GetUnitData();
	vector<Unit_Data*> Unit;
	unsigned int ClientID = 0;

	void ConvertData(string);
	short static CalculateChecksum(string& Message);
private:
	bool CheckChecksumValidation(string& Message);
	Data LastData;
	Data CurrentData;
	json Data;
};

