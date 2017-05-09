#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
namespace Stas {

	class File
	{
	private:
		File();
		~File();
	public:
		static string Read(string path);
		static void Write(string path, string Data);


	};

}
