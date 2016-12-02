#include "TransferedData.h"



TransferedData::TransferedData()
{
}
TransferedData::TransferedData(string DataReceived)
{
	UpdateData(DataReceived, 0);
}

TransferedData::~TransferedData()
{
}
bool TransferedData::UpdateData(string DataReceived, int Counter)
{
	//"[16 checksum][16 id][n msg]";
	//"*Number Of Bytes* {Type Position.x Position.y Position.z Action ClientID} * n";
	////if (DataReceived != "")
	//static int UnitDeletes = 0;
	//unsigned int ModelType = 0;
	//string Space(" ");
	//vec3 Position;
	//unsigned int Action = 0;
	//int firstIndex = 0, secondIndex = 0;
	//if (!CalculateChecksum(DataReceived))
	//{
	//	return false;
	//}
	//for (unsigned int i = 0; i < DataReceived.size(); i++ ) 
	//{
	//	if (DataReceived[i] == ',')
	//	{
	//		DataReceived[i] = '.';
	//	}
	//}
	////DataReceived = DataReceived.replace(DataReceived.begin(), DataReceived.end(), ',', '.');
	//for (unsigned int Unit_Count = 0; DataReceived != ""; Unit_Count++)
	//{
	//	ModelType  = std::stoi(DataReceived.substr(0, secondIndex = DataReceived.find(Space)));
	//	DataReceived = DataReceived.substr(secondIndex + 1, DataReceived.size());
	//	Position.x = std::stof(DataReceived.substr(0, secondIndex = DataReceived.find(Space)));
	//	DataReceived = DataReceived.substr(secondIndex + 1, DataReceived.size());
	//	Position.y = std::stof(DataReceived.substr(0, secondIndex = DataReceived.find(Space)));
	//	DataReceived = DataReceived.substr(secondIndex + 1, DataReceived.size());
	//	Position.z = std::stof(DataReceived.substr(0, secondIndex = DataReceived.find(Space)));
	//	DataReceived = DataReceived.substr(secondIndex + 1, DataReceived.size());
	//	Action	   = std::stoi(DataReceived.substr(0, secondIndex = DataReceived.find(Space)));
	//	DataReceived = DataReceived.substr(secondIndex + 1, DataReceived.size());
	//	ClientID   = std::stoi(DataReceived.substr(0, secondIndex = DataReceived.find(Space)));
	//	DataReceived = DataReceived.substr(secondIndex + 1, DataReceived.size());
	//	if (secondIndex == -1)
	//		DataReceived.clear();
	//	// ClientID = 1 is a non existing Client.
	//	if (ClientID == 0)
	//		continue;
	//	// Keep All existing Units on their place, changing their values.
	//	if (Unit.size() > (Unit_Count))
	//		Unit[Unit_Count]->Update_Unit_Data(Position, "Katarina", Action, Counter); // todo : treat the case of 1 client closing while this one watching it happening
	//	// Add new Units if needed.
	//	else
	//		Unit.push_back(new Unit_Data(Position, "Katarina", Action, Counter, Unit_Count));
	//}
	return true;
}

bool TransferedData::TranslatedData()
{
	Data["Cow"] = "Michael";
	Data = {
		{"Unit", {
			{"x",10},{"y",9},{ "z",8 }
			}
		}
	};
	json StringData;
	Data = StringData.parse("{'x':10.0, 'y' : 20.0, 'z' : 30.0}");
	return false;
}

void TransferedData::ConvertData(string Message)
{
	/*rapidxml::xml_document<char*> xml;
	xml.parse<0>(Message);

	xml = new XMLDocument(Message);
	vector<XMLNodes> Units = xml.GetChildrenByTag("Unit");*/
}

short TransferedData::CalculateChecksum(string & Message)
{
	short Sum = 0;
	for each(char c in Message)
	{
		Sum += c;
	}
	return 0xFF - Sum;

}
bool TransferedData::CheckChecksumValidation(string & Message)
{
	// incomplete message
	if (Message.size() < 2)
		return false;
	short Sum = 0;
	for each(char c in Message)
	{
		Sum += c;
	}
	if (Sum == 0xFF) 
		return true;
	// Failed checksum validation
	else
		return false;
}
vector<Unit_Data*> TransferedData::GetUnitData()
{
	return Unit;
}