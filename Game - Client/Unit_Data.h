#pragma once
#include "glm\glm\vec3.hpp"
#include "Loader.h"
#include "Loaded_Models.h"
using namespace glm;
class Unit_Data
{
public:
	Unit_Data();
	Unit_Data(vec3 Position,vec3 Destination,string ModelIndex);
	void Update_Unit_Data(const vec3 Position, const vec3 Destination);// , const string ModelIndex, const unsigned int, const int);
	vec3 GetPosition() const;
	void SetPosition(const vec3);
	Model* GetModelData() const;
	unsigned int GetClientID() const;
	~Unit_Data();
public:
	vec3 Position;
	vec3 Destination;
	Model* Model_Data;
	unsigned int action;
	Loaded_Models Model;
};	

