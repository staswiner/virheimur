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
	FrameData& frameData = FrameData::Instance();
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

		unit.Position = ModelsCollection::Instance()["Land"]->meshes[0].mCollision->OnCollision(unit.Position);
		
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
	FrameData& frameData = FrameData::Instance();
	mat4 ProjectionMatrix = frameData.ProjectionMatrix;
	mat4 ViewMatrix = frameData.ViewMatrix;
	// Calculate moving position
	OfflineDataObject& OfflineData = OfflineDataObject::Instance();
	GameObject& p = *OfflineData.level.ActivePlayers[0];
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

TODO_FUNCTION void GameLogic::CalculateCollision()
{
#define Is_In_Area_Of_Object true
	vector<GameObject> GameObjects;

	for (auto& object : GameObjects)
	{
		if (Is_In_Area_Of_Object)
		{
			// Model model;
			// model.boundryBox; // homogenic mass distribution; momentum is calculated lineary to position
			// model.boundryBox::area of collision::points of collision;
			// extreme far points of boundry box;
			// apply physics towards each one of vertices here ^ as dot;
			// vector * mass for each dot;
			// combine all vectors in that object to the center of the object;
			   


			// to find collision points : 
			// collision of 2 cubes :
			//	find 3 of the nearest planes towards each other; all have 1 closest vertex in common, for each cube 8 steps, 16 total
			//	check for interception
			//	if interception occured, calculate force by speed of the object.

			// momentum = velocity * mass = F
			// to calculate the velocity on the applied object( object2 ) by the applying object1,( v1 * m1 )/ m2

			Model* objModel = object.unit_Data.Model_Data;
		}
	}
}

TODO_FUNCTION void GameLogic::ProcessForces()
{
	vector<GameObject> GameObjects;

	for (auto& object : GameObjects)
	{
		if (object.unit_Data.HasPhysics)
		{
			object.unit_Data.ForceVector;
			object.unit_Data.Acceleration += object.unit_Data.ForceVector * Time::Instance().Frame();
			object.unit_Data.Position += object.unit_Data.Velocity;
		}
	}
}

void GameLogic::RegisterCollisionBodies()
{
	for (auto object : OfflineDataObject::Instance().level.GameObjects)
	{
		object->CreateCollisionBody(this->world);
	}
}

void GameLogic::UpdateCollisionBodies()
{
	for (auto object : OfflineDataObject::Instance().level.GameObjects)
	{
		object->UpdateCollisionBody(this->world);
	}
}

void GameLogic::CheckCollision()
{
	OfflineDataObject& offlineData = OfflineDataObject::Instance();
	for (auto object1 = offlineData.level.GameObjects.begin();
		object1+1 != offlineData.level.GameObjects.end(); object1++)
	{
		for (auto object2 = object1+1;
			object2 != offlineData.level.GameObjects.end(); object2++)
		{
			this->world.testAABBOverlap((*object1)->collisionBody, (*object2)->collisionBody);
		}
	}
}

void GameLogic::ProcessPlayerMovement()
{
	// Declarations
	FrameData& frameData = FrameData::Instance();
	mat4 ProjectionMatrix = frameData.ProjectionMatrix;
	mat4 ViewMatrix = frameData.ViewMatrix;
	OfflineDataObject& OfflineData = OfflineDataObject::Instance();
	GameObject& p = *OfflineData.level.ActivePlayers[0];
	Unit_Data& ud = p.GetUnitData();

	// Calculate moving position
	if (p.control == GameObject::controls::Script) // even arguements
	{
		p.script(p);
	}
	else if (p.control == GameObject::controls::Manual)
	{

	}
	else if (p.control == GameObject::controls::Direct)
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

	if (p.movement == GameObject::movements::Ground) {
		ud.Position = ModelsCollection::Instance()["Land"]->meshes[0].mCollision->OnCollision(ud.Position);
		vec3 rotation = ModelsCollection::Instance()["Land"]->meshes[0].mCollision->GetNormalRotation(ud.Position.xz);
		
		ud.RotateByNormal(rotation);
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


