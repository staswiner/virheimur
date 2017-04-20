#include "Network.h"



Network::Network(GlobalDataObject& Data)
	:ReceivedData(Data)
{
}



Network::~Network()
{
}

void Network::InitializeConnection()
{
	//bool result = client._Initialize();
	bool result;
	int i = 0;
	do {
		result = udpClient.Initialize();
		i++;
		if (i > 10000)
			exit(1);
	} while (!result);
	hostent * record = gethostbyname("virheimur.com");
	if (record == NULL)
	{
		exit(1);
	}
	in_addr * address = (in_addr *)record->h_addr;
//	address = inet_addr("83.130.207.1");
	ServerIP = inet_ntoa(*address);
	ServerIP = SERVER_ADDRESS;
}

void Network::InitializeLocalConnection()
{
	bool result;
	do {
		result = udpClient.Initialize();
	} while (!result);

	ServerIP = LOCAL_HOST;

	// Send TCP Connection Request
	tcpClient.SendPacket("Connecting<EOF>");
}

void Network::Send(string msg)
{
	//bool result = client._SendMessage(msg);
	//udpClient.Send(msg);
	this->Send(msg, ServerIP, SERVER_PORT_UDP);

}

void Network::Send(string msg, string ip, string port)
{
	udpClient.Send(msg, ip, port);
}

string Network::Receive()
{
	//string msg = client._RecieveMessage();
	//return msg;
	return "";
}

void Network::BeginReceive()
{
	string ReturnData;

	while (1)
	{
		ReturnData = udpClient.Receive();
		if (ReturnData != "")
		{
			int i = 0;
		}
		if (ReturnData == "FIN")
			break;
		if (GetMessageType(ReturnData) == "Data")
		{
			ReceivedData.ReceiveDataString(GetMessageContent(ReturnData));
		}
		if (GetMessageType(ReturnData) == "Authentication")
		{
			InitializeDataAuthentication(GetMessageContent(ReturnData));
			//MyIP = GetMessageContent(ReturnData);
			//GlobalData.SetMyIP(MyIP);
			//SetNewData(GetMessageContent(ReturnData));
			//GlobalData.re
			//MyIP = NewData.GetMyIP();
			//GlobalData.SetMyIP(MyIP);
		}
		if (GetMessageType(ReturnData) == "403")
		{
			Send("Authentication Staswiner s32135417789");
		}
	}
}

void Network::FormConnection()
{
	string Ack;
	do {
		Send("Authentication Username Password", ServerIP, "27045");
		Ack = Receive();
	} while (Ack != "ACK");
}


void Network::SendNewData(GlobalDataObject & NewData)
{
	vector<json> JPlayers;
	milliseconds TimeSinceEpoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	for (auto i = NewData.GetPlayerInformation().begin(); i != NewData.GetPlayerInformation().end(); i++)
	{
		JPlayers.push_back(i->second->GetJson());
	}
	json JNewData(JPlayers);
	string Jstring = "NewData " + Session::Instance().CharacterName + " " +
		to_string(TimeSinceEpoch.count()) + " " + JNewData.dump();
	Send(Jstring);
	int i = 0;
//	JNewData = {NewData.GetPlayerInformation()[""]};
}

void Network::InitializeDataAuthentication(string NewData)
{
	json ParsedData = json::parse(NewData.c_str());

	vec3 Position(ParsedData["x"], ParsedData["y"], ParsedData["z"]);
	vec3 Destination(ParsedData["Destx"], ParsedData["Desty"], ParsedData["Destz"]);

	string ip = ParsedData["IpAddress"];
	this->MyIP = ip;
}

string Network::GetMessageType(string message)
{
	return message.substr(0,message.find(' '));
}

string Network::GetMessageContent(string message)
{
	return message.substr(message.find(' ') + 1);
}
