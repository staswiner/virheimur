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
	static Session instance;
public:
	~Session();
	static Session& Instance()
	{

		static Session instance;
		return instance;
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
	static Core instance;
public:
	~Core() {}
	static Core& Instance()
	{
		static Core instance;
		return instance;
	}
	bool Online;
};
