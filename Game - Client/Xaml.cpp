#include "Xaml.h"

void Xaml::Element::SetAttribute(string Name, string Value)
{
	this->Attributes[Name] = Attribute(Name, Value);
}

string Xaml::Element::GetAttribute(string Name)
{
	if (this->Attributes.find(Name) == this->Attributes.end())
	{
		return "";
	}
	return this->Attributes[Name].Value;
}

void Xaml::AppendChild(Element & element)
{
	this->Root.Children.push_back(element);
}
