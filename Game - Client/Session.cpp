#include "Session.h"



Session::Session()
{
}


Session::~Session()
{
	TCP tcp;
	tcp.SendPacket("GetOffline " + Session::Instance().CharacterName + " <EOF>");
	if (tcp.ReceivePacketsAsync() == "True")
	{
		int i = 0;
	}
}
