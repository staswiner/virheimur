#include "Player.h"



Player::Player(Unit_Data unit_Data,string Username,string IpAddress, int Type)
{
	this->Type = Type;
	this->unit_Data = unit_Data;
	this->IpAddress = IpAddress;
	this->Username = Username;
	this->stats.MovementSpeed = 100;
}


Player::~Player()
{
}

Unit_Data& Player::GetUnitData()
{
	return this->unit_Data;
}

void Player::UpdateUnitData(Unit_Data uData)
{
	this->unit_Data.SetPosition(uData.GetPosition());
}

json Player::GetJson()
{
	json JPlayer;
	JPlayer["x"] = this->unit_Data.Position.x;
	JPlayer["y"] = this->unit_Data.Position.y;
	JPlayer["z"] = this->unit_Data.Position.z;
	JPlayer["Destx"] = this->unit_Data.Destination.x;
	JPlayer["Desty"] = this->unit_Data.Destination.y;
	JPlayer["Destz"] = this->unit_Data.Destination.z;
	JPlayer["IpAddress"] = this->IpAddress;
	JPlayer["Username"] = this->Username;
	return JPlayer;
}

int Player::GetType()
{
	return this->Type;
}
