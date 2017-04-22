#include "GameLogic.h"



GameLogic::GameLogic(GDO& Data)
	:Data(Data)
{
}


GameLogic::~GameLogic()
{
}

void GameLogic::Proceed(GDO& FinalData)
{
	FrameData& frameData = FrameData::GetInstance();
	mat4 ProjectionMatrix = frameData.ProjectionMatrix;
	mat4 ViewMatrix = frameData.ViewMatrix;
	// Calculate moving position
#pragma region bug
	for (auto &p : FinalData.GetPlayerInformation())
	{
		using namespace chrono;
		Unit_Data& unit = p.second->GetUnitData();
		milliseconds currTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		float Delta = float(currTime.count() - unit.StartPointTime.count()) / 1000.0f; // movement delta
		float ServerDelta = float(p.second->TimeDelta.count() - (currTime.count())) / 1000.0f; // sync delta
		float TotalDistance = p.second->stats.MovementSpeed * (Delta + ServerDelta);
		try {

			for (uint i = 1; i < unit.Path.size(); i++)
			{
				vec3 start = unit.Path[i - 1];
				vec3 end = unit.Path[i];
			/*	subscript out of range
					i = 3;
				unit.Path.size() = 7;*/
				float Distance = distance(end, start);
				unit.Destination = unit.Path[i];
				if (TotalDistance > Distance)
					TotalDistance -= Distance;
				else
				{
					unit.Destination = unit.Path[i];
					unit.StartPoint = unit.Path[i - 1];
					unit.Position = glm::normalize(unit.Destination - unit.StartPoint) *
						TotalDistance +
						unit.StartPoint;
					TotalDistance = 0;
					break;
				}
			}
		}
		

		catch (exception ex)
		{
			int i = 0;
		}
		if (TotalDistance > 0)
		{
			unit.StartPoint = unit.Destination;
		}

		if (unit.StartPoint == unit.Destination)
		{
			unit.Position = unit.StartPoint;
		}
		else
		{
		/*	/// position
			unit.Position =
				glm::normalize(unit.Destination - unit.StartPoint) *
				unit.MovementSpeed *
				(Delta + ServerDelta) +
				unit.StartPoint;*/
			/// Rotation
			// inefficient, but either to manage, can be placed on start conditions later on
		
			
				vec3 test = glm::normalize(unit.Destination - unit.StartPoint);
			float test1 = dot(test, vec3(1, 0, 0));
			unit.Rotation.y = -acos(dot(glm::normalize(unit.Destination - unit.StartPoint), vec3(1, 0, 0)));
			(unit.Destination.z - unit.StartPoint.z < 0) ?
				unit.Rotation.y = radians(360.0f) - unit.Rotation.y
				: unit.Rotation.y
				;
		}

		unit.Position = ModelsCollection::getInstance()["Land"]->meshes[0].mCollision->OnCollision(unit.Position);
		
	}
#pragma endregion bug

		//unit.Position = unit.Destination;
		// Test if destination reached or passed
		// Once reached, send server that current position is destination
		////
		//else if (dot(unit.Destination - unit.Position, unit.Destination - unit.StartPoint) < 0)
		//{
		//	unit.StartPoint = unit.Destination;
		//	unit.Position = unit.Destination;
		//	unit.Position = loaded_Models["Land"]->meshes[0].mCollision->OnCollision(unit.Position);
		//	//unit.LocalDestination++;
		//	// to be implement
		///*	unit.Path.pop_front();
		//	if (unit.Path.size() > 0)
		//	{
		//		unit.Destination=unit.Path.front();
		//	}*/
		//	//unit.PathChanged = !(unit.Destination == *unit.Path.end());
		//}
	// Effect lifetimes
	for (auto e = FinalData.Effects.begin(); e != FinalData.Effects.end();)
	{
		if (e->CheckStatus())
		{
			e = FinalData.Effects.erase(e);
		}
		else
		{
			e++;
		}
	}
}

void GameLogic::ProcessDataOffline()
{
	FrameData& frameData = FrameData::GetInstance();
	mat4 ProjectionMatrix = frameData.ProjectionMatrix;
	mat4 ViewMatrix = frameData.ViewMatrix;
	// Calculate moving position
	OfflineDataObject& OfflineData = OfflineDataObject::Instance();
	Player& p = OfflineData.player;
	// Controls movements if scripted or not

	///<Important Function>
	ProcessPlayerMovement();
	///<Important Function/>

	// Effect lifetimes
	for (auto e = OfflineData.Effects.begin(); e != OfflineData.Effects.end();)
	{
		if (e->CheckStatus())
		{
			e = OfflineData.Effects.erase(e);
		}
		else
		{
			e++;
		}
	}
}

void GameLogic::ProcessPlayerMovement()
{
	// Declarations
	FrameData& frameData = FrameData::GetInstance();
	mat4 ProjectionMatrix = frameData.ProjectionMatrix;
	mat4 ViewMatrix = frameData.ViewMatrix;
	OfflineDataObject& OfflineData = OfflineDataObject::Instance();
	Player& p = OfflineData.player;
	Unit_Data& ud = p.GetUnitData();
	// Calculate moving position
	if (p.control == Player::controls::Script) // even arguements
	{
		p.script(p);
	}
	if (p.control == Player::controls::Manual)
	{

	}
	if (p.control == Player::controls::Direct)
	{

	}
	// Rotation
	else if (ud.Destination.xz != ud.StartPoint.xz)
	{
		ud.Rotation.y = -acos(dot(glm::normalize(vec2(ud.Destination.x, ud.Destination.z)
			- vec2(ud.StartPoint.x, ud.StartPoint.z)), vec2(1, 0)));
		// fix Rotation to 360°
		(ud.Destination.z - ud.StartPoint.z < 0) ?
			ud.Rotation.y = radians(360.0f) - ud.Rotation.y : ud.Rotation.y;
	}
	if (p.movement == Player::movements::Ground) {
		ud.Position = ModelsCollection::getInstance()["Land"]->meshes[0].mCollision->OnCollision(ud.Position);
		vec3 rotation = ModelsCollection::getInstance()["Land"]->meshes[0].mCollision->GetNormalRotation(ud.Position);
		ud.Rotation.x = rotation.x;
		ud.Rotation.z = rotation.z;
	}
}
// old moving script
/*
if (p.disablePathing)
{
return;
}
using namespace chrono;
Unit_Data& unit = p.GetUnitData();
milliseconds currTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
float Delta = float(currTime.count() - unit.StartPointTime.count()) / 1000.0f; // movement delta
float TotalDistance = unit.MovementSpeed * (Delta) * 0.5f;
if (p.LongPath)
{

try {

for (int i = 1; i < unit.Path.size(); i++)
{
vec3 start = unit.Path[i - 1];
vec3 end = unit.Path[i];
float Distance = distance(end, start);
unit.Destination = unit.Path[i];
if (TotalDistance > Distance)
TotalDistance -= Distance;
else
{
	unit.Destination = unit.Path[i];
	unit.StartPoint = unit.Path[i - 1];
	unit.Position = glm::normalize(unit.Destination - unit.StartPoint) *
		TotalDistance +
		unit.StartPoint;
	TotalDistance = 0;
	break;
}
			}
		}
		catch (exception ex)
		{
			int i = 0;
		}
		if (TotalDistance > 0)
		{
			unit.StartPoint = unit.Destination;
		}
	}
	else
	{
		unit.Position = glm::normalize(unit.Destination - unit.StartPoint) *
			TotalDistance +
			unit.StartPoint;
	}





	if (unit.StartPoint == unit.Destination)
	{
		unit.Position = unit.StartPoint;
	}
	else
	{

		vec3 test = glm::normalize(unit.Destination - unit.StartPoint);
		float test1 = dot(test, vec3(1, 0, 0));
		unit.Rotation.y = -acos(dot(glm::normalize(vec2(unit.Destination.x, unit.Destination.z) - vec2(unit.StartPoint.x, unit.StartPoint.z)), vec2(1, 0)));

		(unit.Destination.z - unit.StartPoint.z < 0) ?
			unit.Rotation.y = radians(360.0f) - unit.Rotation.y
			: unit.Rotation.y
			;
	}*/
void GameLogic::ChainCommands()
{
	typedef void (GameLogic::*function)();
	struct Script {
		char Key;
		function Func;
	};
	map<char, list<function>> Commands;
	vector<Script> Scripts;
	for each (Script script in Scripts)
	{
		Commands[script.Key].push_back(script.Func);
	}
}


