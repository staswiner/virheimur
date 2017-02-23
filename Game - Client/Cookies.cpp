#include "Cookies.h"



Cookies::Cookies()
{
}


string Cookies::Encrypt(string Text)
{
	return string();
}

Cookies::~Cookies()
{
}

string Cookies::GetCookie(string Field)
{
	TCP tcp;
	if (this->Key == "")
		this->Key = this->GetCookieKey();
	tcp.SendPacket("GetCookie " + Key + " " + Field+" <EOF>");
	string Data = tcp.ReceivePacketsAsync();
	return Data;
}

void Cookies::SetCookie(string Field, string Data)
{
	TCP tcp;
	if (this->Key == "")
		this->Key = this->GetCookieKey();
	tcp.SendPacket("SetCookie " + Key + " " + Field + " " + Data + " <EOF>");
	tcp.ReceivePacketsAsync();
}

void Cookies::GenerateKey()
{
	string RandomString;
	for (int i = 0; i < (rand() % 10) + 10; i++)
	{
		RandomString += rand() % 255;
	}

	ofstream myfile;
	myfile.open("cookies.txt");
	myfile << RandomString;
	myfile.close();

	TCP tcp;
	tcp.SendPacket("SetCookieKey "+ RandomString +" <EOF>");
	tcp.ReceivePacketsAsync();
}

string Cookies::GetCookieKey()
{
	string line;
	ifstream myfile("cookies.txt");
	if (myfile.is_open())
	{
		getline(myfile, line);
		myfile.close();
	}
	else
	{
		GenerateKey();
		line = GetCookieKey();
	}


	return line;
}
