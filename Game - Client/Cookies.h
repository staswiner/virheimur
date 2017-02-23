#pragma once
#include <string>
#include "TCP.h"
using namespace std;
class Cookies
{
private:
	Cookies();
	Cookies(Cookies const&) = delete;
	void operator=(Cookies const&) = delete;
	static Cookies Instance;
	static string Encrypt(string Text);

	string Key;
	void GenerateKey();
	string GetCookieKey();
public:
	~Cookies();
	static Cookies& GetInstance()
	{
		static Cookies Instance;
		return Instance;
	}
	string GetCookie(string Field);
	void SetCookie(string Field, string Data);
};


