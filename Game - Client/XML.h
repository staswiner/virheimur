#pragma once
#include <vector>
#include <map>
#include <exception>
#include <iostream>
#include "File.h"
class XML
{
public:
	XML() {}
	~XML() {}
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
class XMLReader
{
public:
	XMLReader();
	~XMLReader();
	XML Read(string Filename);
private:
	class ReaderException : public exception {
	public:
		ReaderException(const char* Message) :Message(Message) {}
		virtual const char* what() const throw() {
			return Message;
		}
	private:
		const char* Message;
	};
	enum class Result
	{
		Valid,
		Error
	};
	string Organize(string Content);
	Result CheckValidation(string Content);
	int ReadToken(string Content, int Position, string Expected);
	// returns start position of found token
	int MatchFirstOf(string Content, vector<string> Tokens, /*vector<string> regexes,*/string& Token, int Offset);

	int ReadElements(string Tag, XML::Element& element);
	int ReadAttributes(string Element, XML::Element& element);
};
