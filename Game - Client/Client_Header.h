#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <thread>
//#include <future>
#include "TransferedData.h"


using namespace std;


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 1024
#define SERVER_PORT_TCP "27047"
#define SERVER_PORT_UDP "27045"
#define CLIENT_PORT_UDP "27047"
#define CLIENT_ADDRESS "83.130.220.189"
#define SERVER_ADDRESS "83.130.220.189"
#define LOCAL_HOST "127.0.0.1"
