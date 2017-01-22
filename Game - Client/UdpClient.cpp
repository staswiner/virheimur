#include "UdpClient.h"



UdpClient::UdpClient()
{
}


UdpClient::~UdpClient()
{
	closesocket(s);
	WSACleanup();
}

bool UdpClient::Initialize()
{
	slen = sizeof(si_other);

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		// Failed
		return false;
	}
	
	//create socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		//socket fail
		return false;
	}

	//setup address structure
	memset((char *)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(stoi(SERVER_PORT_UDP));
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER_ADDRESS);
	int err = WSAGetLastError();

	//Prepare the sockaddr_in structure
	// The Receiver component of the Client
	server.sin_family = AF_INET;
	server.sin_port = htons(stoi(CLIENT_PORT_UDP));
	server.sin_addr.s_addr = INADDR_ANY;

	// Set timeout to 5seconds
	//struct timeval tv;
	//tv.tv_sec = 0;
	//tv.tv_usec = 1;

	//if (setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&tv), sizeof(tv)) < 0) {
	//	perror("Error");
	//}
	//Bind
	if (::bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		int err = WSAGetLastError();
		return false;
	}

	return true;
}

bool UdpClient::Send(string msg)
{
	//send the message
	if (sendto(s, msg.c_str(), msg.size(), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}
// sends message to custom ip/port
bool UdpClient::Send(string msg, string ip, string port)
{
	sockaddr_in si_custom;
	int s_custom;
	//create socket
	if ((s_custom = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		//socket fail
		return false;
	}

	//setup address structure
	memset((char *)&si_custom, 0, sizeof(si_custom));
	si_custom.sin_family = AF_INET;
	si_custom.sin_port = htons(stoi(port));
	si_custom.sin_addr.S_un.S_addr = inet_addr(ip.c_str());

	// config timeout
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 10000;
	if (setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&tv), sizeof(tv)) < 0) {
		perror("Error");
	}
	//send the message
	if (sendto(s, msg.c_str(), msg.size(), 0, (struct sockaddr *) &si_custom, slen) == SOCKET_ERROR)
	{
		closesocket(s_custom);
		return false;
	}
	closesocket(s_custom);
	return true;
}

string UdpClient::Receive()
{
	// waiting for data
	fflush(stdout);

	//clear the buffer by filling null, it might have previously received data
	memset(buf, '\0', DEFAULT_BUFLEN);

	//try to receive some data, this is a blocking call
	if ((recv_len = recvfrom(s, buf, DEFAULT_BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
	{
		int fail = WSAGetLastError();
		// receive failed
		printf("recvfrom() failed with error code : %d", WSAGetLastError());
		return "";
	}
	
	//print details of the client/peer and the data received
	string Recaddress = inet_ntoa(si_other.sin_addr);
	printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
	printf("Data: %s\n", buf);
	Send("Got it", inet_ntoa(si_other.sin_addr), to_string(ntohs(si_other.sin_port)));
	return string(buf);
}