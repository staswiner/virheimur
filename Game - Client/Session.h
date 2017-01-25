#pragma once
#include "string"
#include "TCP.h"
using namespace std;
class Session
{
private:
	Session();
	Session(Session const&) = delete;
	void operator=(Session const&) = delete;
	static Session Instance;
public:
	~Session();
	static Session& GetInstance()
	{
		static Session Instance;
		return Instance;
	}
	string Username;
	string UserID;
	string CharacterID;
	string CharacterName;
};

