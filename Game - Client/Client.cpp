#include "Client.h"



Client::Client(int*, char**)
{
}

Client::Client()
{

}
Client::~Client()
{
}
bool Client::_SendMessage(string Message)
{
	// Send an initial buffer
	/*yhread Send(send, ConnectSocket, Message.c_str(), Message.size(), 0);*/
	iResult = send(ConnectSocket, Message.c_str(), Message.size(), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	return 0;
}
string Client::_RecieveMessage()
{
	char recvbuf[512] = { 0 };
	/*Receive = thread(recv, ConnectSocket, recvbuf, 512, 0);*/
	/*Receive.join();*/
	iResult = recv(ConnectSocket, recvbuf, 512, 0);
	return string(recvbuf);
}
string hi()
{
	return string();
}
string Client::_AsyncReceiveMessage()
{
	//future<string> bye = async(hi);
	//future<string> ReceivedString = async(&Client::_RecieveMessage, this);

	//while (!ReceivedString._Is_ready());
	return _RecieveMessage();
}
bool Client::_CloseConnection(int index)
{
	// shutdown the connection since no more data will be sent
	ostringstream ClientIDoss;
	ClientIDoss << index;
	this->_SendMessage(string("ClientID ") + ClientIDoss.str());
	//this->_RecieveMessage();
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	// Receive until the peer closes the connection
	do {

		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (string(recvbuf) == "Close Connection")
		{
			break;
		}
		
		if (iResult > 0)
			printf("Bytes received: %d\n", iResult);
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed with error: %d\n", WSAGetLastError());

	} while (iResult > 0);

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();
	cin.get();
	return 0;
}
bool Client::_Initialize()
{
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;

	// Resolve the server address and port
	string Adress(SERVER_ADDRESS);
	iResult = getaddrinfo(Adress.c_str(), DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}
	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; /*ptr = ptr->ai_next*/) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}

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
		return 1;
	}
	/*this->_SendMessage("Receive ClientID");
	TransferedData InitialSpot 
	string sIndex = this->_RecieveMessage();
	this->ClientIndex = std::stoi(sIndex);*/

	return false;
}
