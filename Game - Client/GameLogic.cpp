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
	for (auto &p : FinalData.GetPlayerInformation())
	{
		using namespace chrono;
		Unit_Data& unit = p.second.GetUnitData();
		milliseconds currTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		float Delta = float(currTime.count() - unit.StartPointTime.count())/1000.0f;
		// Set Position Based on destination,time vector
		unit.Position =
			glm::normalize(unit.LocalDestination - unit.Position) *
			unit.MovementSpeed * 
			Delta;
		unit.Position = loaded_Models["Land"]->meshes[0].mCollision->OnCollision(unit.Position);
		
		//unit.Position = unit.Destination;
		// Test if destination reached or passed
		// Once reached, send server that current position is destination
		if (dot(unit.LocalDestination - unit.Position, unit.LocalDestination - unit.StartPoint) < 0)
		{
			unit.Position = unit.LocalDestination;
			//unit.LocalDestination++;
			unit.Destination.pop_front();
			if (unit.Destination.size() > 0)
			{
				unit.LocalDestination++;
			}
			unit.PathChanged = !(unit.LocalDestination == *unit.Destination.end());
			unit.StartPointTime = currTime;
		}
	}

	//// Calculate moving position
	//if (Data.GetPlayerInformation().find(Data.MyUsername) == Data.GetPlayerInformation().end())
	//{

	//}
	//else
	//{

	//	Unit_Data& MyPlayerPositionNew = NewData.GetPlayerInformation()[Data.MyUsername].GetUnitData();
	//	Unit_Data& MyPlayerPosition = Data.GetPlayerInformation()[Data.MyUsername].GetUnitData();
	//	if (glm::length(MyPlayerPositionNew.Destination) - glm::length(MyPlayerPosition.Position) > 10)
	//	{
	//		vec3 Direction = normalize(MyPlayerPositionNew.Destination - MyPlayerPosition.Position);
	//		MyPlayerPositionNew.Position = (Direction) *
	//			((float)NewData.GetPlayerInformation()[Data.MyUsername].stats.MovementSpeed / 10.0f)
	//			+ MyPlayerPosition.Position;
	//	}
	//}
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

void GameLogic::BuildData() // xml not working
{
	/*tinyxml2::XMLDocument xml;
	tinyxml2::XMLElement * element;
	tinyxml2::XMLElement * elementNext;
	vec3 Position;
	xml.NewText("<scene><map>1</map><units></units></scene");
	element = xml.FirstChildElement("units");
	element->SetAttribute("type", "katarina");
	elementNext = xml.NewElement("x");
	elementNext->SetValue(to_string(Position.x).c_str());
	element->InsertEndChild(elementNext);
	elementNext = xml.NewElement("y");
	elementNext->SetValue(to_string(Position.y).c_str());
	element->InsertEndChild(elementNext);
	elementNext = xml.NewElement("z");
	elementNext->SetValue(to_string(Position.z).c_str());
	element->InsertEndChild(elementNext);*/

}
