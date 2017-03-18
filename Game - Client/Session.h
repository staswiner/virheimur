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
class Core
{
private:
	Core() {}
	Core(Core const&) = delete;
	void operator=(Core const&) = delete;
	static Core Instance;
public:
	~Core() {}
	static Core& GetInstance()
	{
		static Core Instance;
		return Instance;
	}
	bool Online;
};
