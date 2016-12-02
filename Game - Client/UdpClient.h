#pragma once
#include "Client_Header.h"
class UdpClient
{
public:
	UdpClient();
	~UdpClient();
	bool Initialize();
	bool Send(string);
	bool Send(string, string, string);
	string Receive();
private:
	struct sockaddr_in si_other, server;
	int s, slen, recv_len;
	int ReceiveSocket, SendSocket;
	char buf[DEFAULT_BUFLEN];
	char message[DEFAULT_BUFLEN];
	WSADATA wsa;
};

