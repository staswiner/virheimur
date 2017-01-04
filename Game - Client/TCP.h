#pragma once

#include "Client_Header.h"
class TCP
{
public:
	TCP();
	~TCP();
	void Initialize();
	void Connect();
	void SendPacket();
	void ReceivePacket();
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
};
