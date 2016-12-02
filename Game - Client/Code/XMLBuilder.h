#pragma once
#include <string>
#include <map>
#include <list>
using namespace std;
class XMLBuilder
{
public:
	XMLBuilder();
	~XMLBuilder();
	map<string, XMLBuilder> Node;

	class XMLnode
	{
	public:
		XMLnode();
		~XMLnode();
	};
	class XMLelement
	{
	public:
		XMLelement();
		~XMLelement();
	};
};

