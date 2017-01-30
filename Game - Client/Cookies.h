#pragma once
#include <string>
using namespace std;
class Cookies
{
private:
	Cookies();
	Cookies(Cookies const&) = delete;
	void operator=(Cookies const&) = delete;
	static Cookies Instance;
	static string Encrypt(string Text);
public:
	~Cookies();
	static Cookies& GetInstance()
	{
		static Cookies Instance;
		return Instance;
	}
	static string GetCookie(string Field);
	static void SetCookie(string Field, string Data);
};


