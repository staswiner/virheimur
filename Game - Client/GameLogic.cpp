#include "GameLogic.h"



GameLogic::GameLogic(GDO& Data)
	:Data(Data)
{
}


GameLogic::~GameLogic()
{
}

void GameLogic::Proceed(GDO& FinalData,mat4& ProjectionMatrix, mat4& ViewMatrix)
{
	// Calculate moving position
	// TODO: CRASHES IN THIS FUNCTION SOMEWHERE
#pragma region bug
	for (auto &p : FinalData.GetPlayerInformation())
	{
		using namespace chrono;
		Unit_Data& unit = p.second->GetUnitData();
		milliseconds currTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		float Delta = float(currTime.count() - unit.StartPointTime.count()) / 1000.0f; // movement delta
		float ServerDelta = float(p.second->TimeDelta.count() - (currTime.count())) / 1000.0f; // sync delta
		float TotalDistance = unit.MovementSpeed * (Delta + ServerDelta);
		try {

			for (int i = 1; i < unit.Path.size(); i++)
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

		unit.Position = loaded_Models["Land"]->meshes[0].mCollision->OnCollision(unit.Position);
		
	}
#pragma endregion bug

		//unit.Position = unit.Destination;
		// Test if destination reached or passed
		// Once reached, send server that current position is destination
		//if (unit.Destination == unit.StartPoint)
		//{

		//}
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


