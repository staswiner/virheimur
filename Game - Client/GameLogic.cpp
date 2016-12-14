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
		if (unit.Destination != unit.StartPoint)
		{
			p.second.unit_Data.Position =
				glm::normalize(unit.Destination - unit.StartPoint) *
				unit.MovementSpeed *
				Delta + unit.StartPoint;
			//p.second.unit_Data.Position = loaded
		}

		// Test if destination reached or passed
		// Once reached, send server that current position is destination
		if (dot(unit.Destination - unit.Position, unit.Destination - unit.StartPoint) < 0)
		{
			unit.Path.pop_front();
			if (unit.Path.size() > 0)
			{
				unit.Destination = unit.Path.front();
			}
			unit.StartPoint = unit.Destination;
			int i = 0;
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
