#pragma once

#include "Client_Header.h"
class TCP
{
public:
	TCP();
	~TCP();
	void SendPacket(string Data);
	string ReceivePacketsAsync();
private:
	void Connect();
	void Initialize();
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;
};

