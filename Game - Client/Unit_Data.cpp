#include "Unit_Data.h"



Unit_Data::Unit_Data()
{
}
Unit_Data::Unit_Data(vec3 Position,vec3 Destination, string ModelIndex)
{
	this->Position = Position;
	this->Destination = Destination;
	this->Model_Data = Model[ModelIndex];
//	this->Unit_Position.y += 2.0f * (sin(radians(float(Counter))) + 1.0);
}
void Unit_Data::Update_Unit_Data(const vec3 Position, const vec3 Destination)// , const string ModelIndex, const unsigned int Action, const int Counter)
{
	this->Position = Position;
	this->Destination = Destination;
	//	this->Unit_Position.y += 2.0f * (sin(radians(float(Counter))) + 1.0);
	//	this->Model_Data = Model[ModelIndex];
	//this->action = Action;
}

Unit_Data::~Unit_Data()
{
}
vec3 Unit_Data::GetPosition() const
{
	return this->Position;
}
void Unit_Data::SetPosition(const vec3 Position)
{
	this->Position = Position;
}
void Unit_Data::SetDestination(const vec3 & Destination)
{
	this->Destination = Destination;
}
Model* Unit_Data::GetModelData() const
{
	return this->Model_Data;
}
