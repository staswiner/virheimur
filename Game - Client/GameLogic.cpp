#include "GameLogic.h"



GameLogic::GameLogic(GDO& Data)
	:Data(Data)
{
}


GameLogic::~GameLogic()
{
}

void GameLogic::Proceed(GDO& NewData,mat4& ProjectionMatrix, mat4& ViewMatrix)
{
	//if (mouse.RightIsPressed())
	//{
	//	inGameInteractions.Proceed(ProjectionMatrix, ViewMatrix);
	//}
	// Calculate moving position
	if (Data.GetPlayerInformation().find(Data.MyUsername) == Data.GetPlayerInformation().end())
	{

	}
	else
	{

		Unit_Data& MyPlayerPositionNew = NewData.GetPlayerInformation()[Data.MyUsername].GetUnitData();
		Unit_Data& MyPlayerPosition = Data.GetPlayerInformation()[Data.MyUsername].GetUnitData();
		if (glm::length(MyPlayerPositionNew.Destination) - glm::length(MyPlayerPosition.Position) > 10)
		{
			vec3 Direction = normalize(MyPlayerPositionNew.Destination - MyPlayerPosition.Position);
			MyPlayerPositionNew.Position = (Direction) *
				((float)NewData.GetPlayerInformation()[Data.MyUsername].stats.MovementSpeed / 10.0f)
				+ MyPlayerPosition.Position;
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
