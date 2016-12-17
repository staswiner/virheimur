#include "GlobalDataObject.h"


GlobalDataObject::GlobalDataObject(const GlobalDataObject & newData)
	:Players(newData.Players)
{
}

GlobalDataObject::GlobalDataObject(PlayerRepository & Players)
	:Players(Players)
{
}


GlobalDataObject::~GlobalDataObject()
{
}

GlobalDataObject & GlobalDataObject::operator=(const GlobalDataObject & rhs)
{
	if (this != &rhs)
	{
		this->~GlobalDataObject();
		new (this) GlobalDataObject(rhs);
	}

	return *this;
}

void GlobalDataObject::Clear()
{
	this->Players.clear();
}

void GlobalDataObject::TestInit()
{
	/*Players["123.12.123.12"] = Player(Unit_Data(vec3(), "Katarina", 0, 0, 0));
	Players["123.12.123.13"] = Player(Unit_Data(vec3(), "Katarina", 0, 0, 0));*/
}

void GlobalDataObject::ReceiveDataString(string Message)
{
	/*Data["Cow"] = "Michael";
	Data = {
		{ "Unit",{
			{ "x",10 },{ "y",9 },{ "z",8 }
		}
		}
	};
	string SendData = Data.dump(4);
	json StringData;
	json::parse("{\"x\":10.0, \"y\" : 20.0, \"z\" : 30.0}");*/
	try {
		Data = json::parse(Message.c_str());
		json Array = {1,2,3,4,5};
	//	Players.resize(Data.size()); // bad aproach, easy aproach
		//map<string, Player>::iterator it = Players.begin();
	
		for (int i = 0; i < Data.size(); i++)
		{
			json PlayerParsed = Data[i];
			vec3 StartPoint(PlayerParsed["x"], PlayerParsed["y"], PlayerParsed["z"]);
			vec3 Destination(PlayerParsed["Destx"], PlayerParsed["Desty"], PlayerParsed["Destz"]);
			
			if (auto test = abs(milliseconds(PlayerParsed["TimeDelta"]).count()) > 10000)
			{//exception
				int i = 0;
			}
			
			string s = PlayerParsed["IpAddress"];
			string Jusername = PlayerParsed["Username"];
			Players[PlayerParsed["Username"]]->unit_Data.StartPoint = StartPoint;
			Players[PlayerParsed["Username"]]->unit_Data.Destination = Destination;
			Players[PlayerParsed["Username"]]->unit_Data.StartPointTime = milliseconds(PlayerParsed["StartTime"]);
			Players[PlayerParsed["Username"]]->Username = Jusername;
			Players[PlayerParsed["Username"]]->TimeDelta = milliseconds(PlayerParsed["TimeDelta"]); 
		}
	}
	catch (exception ex)
	{
		// string exception = sex
		auto sex = ex;
	}
}

PlayerRepository & GlobalDataObject::GetPlayerInformation() 
{
	return this->Players;
}
