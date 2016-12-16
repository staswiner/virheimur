#pragma once
//#include "Client.h"
#include "Client_Header.h"
#include "UdpClient.h"
#include "GlobalDataObject.h"
#include <chrono>
class Network
{
public:
	//Network() {}
	Network(GlobalDataObject&);
	~Network();
	void InitializeConnection();
	void Send(string);
	void Send(string, string ip, string port);
	string Receive();
	void BeginReceive();
	void FormConnection();
	void SendNewData(GlobalDataObject&);
	void InitializeDataAuthentication(string NewData);
private:
	string GetMessageType(string message);
	string GetMessageContent(string message);
	//Client client;
	UdpClient udpClient;
	GlobalDataObject& ReceivedData;
	//GlobalDataObject NewData;
	string ServerIP;
	string MyIP;

};

