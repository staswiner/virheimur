#pragma once
#include <vector>
#include <map>
#include <exception>
#include <iostream>
#include "File.h"
class Xaml
{
public:
	Xaml() {}
	~Xaml() {}
	struct Attribute {
		Attribute() {}
		Attribute(string Name, string Value) { this->Name = Name; this->Value = Value; }
		string Name;
		string Value;
	};
	struct Element {
		Element() {}
		Element(string Tag) {
			this->Tag = Tag;
		}
		void SetAttribute(string Name, string Value);
		string GetAttribute(string Name);
		string Tag;
		map<string, Attribute> Attributes;
		vector<Element> Children;
	};
	void AppendChild(Element& element);
	Element Root;
};