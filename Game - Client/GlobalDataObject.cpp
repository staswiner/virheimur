#include "GlobalDataObject.h"



GlobalDataObject::GlobalDataObject()
{
	/*Players["123.12.123.12"] = Player(Unit_Data(vec3(), "Katarina", 0, 0, 0));
	Players["123.12.123.13"] = Player(Unit_Data(vec3(), "Katarina", 0, 0, 0));*/
}


GlobalDataObject::~GlobalDataObject()
{
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
			vec3 Position(PlayerParsed["x"], PlayerParsed["y"], PlayerParsed["z"]);
			vec3 Destination(PlayerParsed["Destx"], PlayerParsed["Desty"], PlayerParsed["Destz"]);

			string s = PlayerParsed["IpAddress"];
			string Jusername = PlayerParsed["Username"];
			Players[PlayerParsed["Username"]].UpdateUnitData(Unit_Data(Position, Destination, "Lara"));
			Players[PlayerParsed["Username"]].Username = Jusername;
		}
	}
	catch (exception ex)
	{
		// string exception = sex
		auto sex = ex;
	}
}

void GlobalDataObject::UpdateMyPlayer(Player PlayerData, string Username)
{
	/*json PlayerParsed;
	PlayerParsed["Username"] = Username;
	PlayerParsed["x"] = PlayerData.GetUnitData().GetPosition().x;
	PlayerParsed["y"] = PlayerData.GetUnitData().GetPosition().y;
	PlayerParsed["z"] = PlayerData.GetUnitData().GetPosition().z;
	Data = PlayerParsed;*/
	vec3 Position = PlayerData.GetUnitData().Position;
	vec3 Destination = PlayerData.GetUnitData().LocalDestination;
	
	//Players[Username] = Player(Unit_Data(Position, Destination,
	//	"Lara"),Username);
	Players[Username] = PlayerData;
}

map<string,Player> & GlobalDataObject::GetPlayerInformation() 
{
	return this->Players;
}
