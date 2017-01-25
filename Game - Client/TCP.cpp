#include "TCP.h"



TCP::TCP()
{
}


TCP::~TCP()
{
}
// TODO: remove exit functions
void TCP::Initialize()
{
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
	}
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	// replaced to localhost
	iResult = getaddrinfo(SERVER_ADDRESS, SERVER_PORT_TCP, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
	}
}

void TCP::Connect()
{
	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			exit(1);
		}
		//// Check if connection available
		//::select(0,&ConnectSocket
		//	_In_    int                  nfds,
		//	_Inout_ fd_set               *readfds,
		//	_Inout_ fd_set               *writefds,
		//	_Inout_ fd_set               *exceptfds,
		//	_In_    const struct timeval *timeout
		//);
		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		// Error
	}
}

void TCP::SendPacket(string Data)
{
	this->Initialize();
	this->Connect();
	// Send an initial buffer
	iResult = send(ConnectSocket, Data.c_str(), Data.size(), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
	}

	printf("Bytes Sent: %ld\n", iResult);

	// shutdown the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
	}
}

string TCP::ReceivePacketsAsync()
{
	string ReceivedString;
	// Receive until the peer closes the connection
	do {

		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
		{
			ReceivedString += recvbuf;
		}
		else if (iResult == 0)
			printf("Connection closed\n");
		else
		{
			int recieveError = WSAGetLastError();
		}

	} while (iResult > 0);

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();
	//success
	// remove <EOF>
	return ReceivedString.substr(0,ReceivedString.find("<EOF>"));
}
