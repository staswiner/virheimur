#pragma once
#include "Client_Header.h"
class Client
{
public:
	Client(int*, char**);
	Client();
	~Client();
	bool _Initialize();
	bool _SendMessage(string);
	string _RecieveMessage();
	bool _CloseConnection(int index);
	string _AsyncReceiveMessage();
private:
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	char *sendbuf = "this is a test";
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;
	int *argc;
	int a = 5;
	char **argv;
	int ClientIndex;
	thread Receive;
};

