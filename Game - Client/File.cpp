#include "File.h"


using namespace Stas;
File::File()
{
}


File::~File()
{
}

string Stas::File::Read(string path)
{
	string line;
	string Text;
	ifstream myfile(path);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			Text += line + '\n';
		}
		myfile.close();
	}
	else
	{
		throw exception("unable to open file");
	}
	return Text;
}

void Stas::File::Write(string path, string Data)
{
	string line;
	ofstream myfile(path);
	if (myfile.is_open())
	{
		myfile << Data;
		myfile.close();
	}
	else
	{
		throw exception("unable to open file");
	}
}