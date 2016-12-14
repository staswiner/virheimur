#pragma once
#include "glm\glm\vec3.hpp"
#include "Model.h"
#include "Loaded_Models.h"
#include <chrono>
using namespace chrono;
using namespace glm;
class Unit_Data
{
public:
	Unit_Data();
	Unit_Data(vec3 Position,vec3 Destination,string ModelIndex);
	void Update_Unit_Data(const vec3 Position, const vec3 Destination);// , const string ModelIndex, const unsigned int, const int);
	vec3 GetPosition() const;
	void SetPosition(const vec3);
	void SetDestination(const vec3&);
	Model* GetModelData() const;
	unsigned int GetClientID() const;
	~Unit_Data();
	// When destination is chosen, StartPointTime is updated with the action time. 
	// Later Calculates the route based on this factor and walking speed
public:
	vec3 StartPoint;
	vec3 Position;
	list<vec3> Destination;
	vec3 LocalDestination;
	bool PathChanged = false;
	milliseconds StartPointTime;
	float MovementSpeed = 10;
	Model* Model_Data;
	unsigned int action;
	Loaded_Models Model;
};	

