#include "XML.h"

void XML::Element::SetAttribute(string Name, string Value)
{
	this->Attributes[Name] = Attribute(Name, Value);
}

string XML::Element::GetAttribute(string Name)
{
	if (this->Attributes.find(Name) == this->Attributes.end())
	{
		return "";
	}
	return this->Attributes[Name].Value;
}

void XML::AppendChild(Element & element)
{
	this->Root.Children.push_back(element);
}



XMLReader::XMLReader()
{
}


XMLReader::~XMLReader()
{
}

XML XMLReader::Read(string Filename)
{
	string Content = Stas::File::Read(Filename);
	Content = Organize(Content);
	try {
		//	CheckValidation(Content);
	}
	catch (exception& e)
	{
		cout << e.what();
		exit(1);
	}
	XML xaml;
	string Token;
	int RootOpen = MatchFirstOf(Content, { "<root>" }, Token, 0);
	int RootClose = MatchFirstOf(Content, { "</root>" }, Token, 0);
	XML::Element root("root");

	int SubStrStart = RootOpen + Token.size();
	ReadElements(Content.substr(SubStrStart, RootClose - SubStrStart), root);
	xaml.Root = root;


	//for (int i = 0; i < Content.size(); i++)
	//{
	//	if (Content.substr(i, 1) == "<" && Content.substr(i, 2) != "</")
	//	{
	//		int WordStart = i + 1;
	//		int TagEnd = Content.find(">", i);
	//		int WordEnd = Content.find_first_of(" >", i);
	//		XML::Element element(Content.substr(WordStart, WordEnd - WordStart));
	//		i = WordEnd;
	//		// Attributes
	//		while (i < TagEnd) {
	//			WordStart = i + 1;
	//			WordEnd = Content.find_first_of(' =', i);
	//			int ValueStart = Content.find_first_of("\"", WordEnd) + 1;
	//			int ValueEnd = Content.find_first_of("\"", ValueStart);
	//			element.SetAttribute(Content.substr(WordStart, WordEnd - WordStart),
	//				Content.substr(ValueStart, ValueEnd - ValueStart));
	//			i = Content.find_first_of(" /", ValueEnd);
	//		}
	//		xaml.AppendChild(element);
	//	}
	//}
	return xaml;
}

string XMLReader::Organize(string Content)
{
	/// <Comments>
	for (int i = 0; i < Content.size() - 4; i++)
	{
		if (Content.substr(i, 4) == "<!--")
		{
			int CommentStartIndex = i;
			while (i < Content.size() - 3 && Content.substr(i, 3) != "-->")
			{
				i++;
			}
			Content.erase(CommentStartIndex, i - CommentStartIndex + 3);
			i -= 3;
		}
		if (Content.substr(i, 2) == "<?")
		{
			int CommentStartIndex = i;
			while (i < Content.size() - 2 && Content.substr(i, 2) != "?>")
			{
				i++;
			}
			Content.erase(CommentStartIndex, i - CommentStartIndex + 2);
			i -= 2;
		}
	}
	/// <tabs,new lines>
	for (int i = 0; i < Content.size(); i++)
	{
		if (Content[i] == '\n' || Content[i] == '\r' || Content[i] == '\t')
			Content[i] = ' ';
	}
	/// <tabs,new lines>
	char LastChar = 0;
	for (int i = 0; i < Content.size(); i++)
	{
		if (Content[i] == ' ' && LastChar == ' ')
		{
			Content.erase(i, 1);
			i -= 1;
		}
		LastChar = Content[i];
	}
	return Content;
}

XMLReader::Result XMLReader::CheckValidation(string Content)
{
	int TagCount = 0;
	int FullTagCount = 0;
	bool Open = false;
	for (int i = 0; i < Content.size(); i++)
	{
		string Token;
		int pos = MatchFirstOf(Content, { "<","</","/>", ">" }, Token, i);
		if (pos == -1) {
			cout << "end" << endl;
			return Result::Valid;
		}
		if (Token == "<") {
			if (Open == true)
				throw ReaderException("Tag within Tag");
			TagCount++;
			FullTagCount++;
			Open = true;
			i = pos + 1;
		}
		if (Token == "</") {
			if (Open == true)
				throw ReaderException("Tag within Tag");
			TagCount++;
			FullTagCount++;
			Open = true;
			i = pos + 1;
		}
		else if (Token == "/>")
		{
			if (Open == false)
				throw ReaderException("Tag within Tag");
			TagCount--;
			FullTagCount--;
			Open = false;
			i = pos + 2;
		}
		else if (Token == ">")
		{
			if (Open == false)
				throw ReaderException("Tag within Tag");
			TagCount--;
			Open = false;
			i = pos + 1;
		}
		cout << "Found Token : " << Token << endl;
		if (TagCount < 0) throw ReaderException("More Enclosing Tags than Opening Tags");
	}
	if (TagCount != 0 || FullTagCount < 0) throw ReaderException("Not all Tags Closed");


	return Result::Valid;
}

int XMLReader::ReadToken(string Content, int Position, string Expected)
{

	return 0;
}

int XMLReader::MatchFirstOf(string Content, vector<string> Tokens,/* vector<string> regexes,*/ string & Token, int Offset)
{
	// token, count
	vector<pair<string, int>> TokensCount;
	// regular expression
	// ranges char to char
	vector<pair<vector<pair<char, char>>, int>> RegexesCount;
	for (auto t : Tokens)
	{
		TokensCount.push_back(make_pair(t, 0));
	}
	/*for (auto t : regexes)
	{
	RegexesCount.push_back(make_pair(vector<pair<char, char>>(), 0));
	for (int i = 0; i < t.size(); i++)
	{
	if (t[i] == '-')
	{
	i++;
	RegexesCount.back().first.back().second = t[i];
	}
	else
	{
	RegexesCount.back().first.push_back(make_pair(t[i], t[i]));
	}
	}
	}*/
	string ReturnCandidate;
	for (int i = Offset; i < Content.size(); i++)
	{
		pair<int, bool> HighestMatch = { 0,false };
		for (auto& t : TokensCount)
		{
			if (t.first[t.second] == Content[i])
			{
				t.second++;
				if (t.second > HighestMatch.first)
				{
					HighestMatch.first = t.second;
					HighestMatch.second = true;
				}
				else if (t.second == HighestMatch.first)
				{
					HighestMatch.second = false;
				}
				if (t.second == t.first.size())
				{
					if (t.first.size() > ReturnCandidate.size())
						ReturnCandidate = t.first;
				}
			}
			else
			{
				t.second = 0;
			}
		}
		if ((HighestMatch.second == true && ReturnCandidate.size() > 0))
		{
			Token = ReturnCandidate;
			return i - Token.size() + 1;
		}
		if (HighestMatch.first == 0 && ReturnCandidate.size() > 0)
		{
			Token = ReturnCandidate;
			return i - Token.size();
		}
	}
	return -1;
}
// Tag = <...... >
int XMLReader::ReadElements(string ElementsStr, XML::Element & element)
{
	int ElementIndex = 0;
	for (int i = 0; i < ElementsStr.size(); i++)
	{
		string Token;
		string uselessToken;
		int pos;
		pos = MatchFirstOf(ElementsStr, { "<" }, Token, i);
		int OpenTag = pos + Token.size();
		int TagNameEnd = MatchFirstOf(ElementsStr, { " ",">", "/>" }, Token, OpenTag);
		pos = MatchFirstOf(ElementsStr, { ">", "/>" }, Token, OpenTag);
		int ClosingTag = pos + Token.size();
		int OpeningElement = ClosingTag;

		string TagName = ElementsStr.substr(OpenTag, TagNameEnd - OpenTag);
		element.Children.push_back(XML::Element(TagName));
		// Has no attributes, has children
		if (Token == ">")
		{
			pos = MatchFirstOf(ElementsStr, { "</" + TagName + ">" }, Token, OpenTag);
			//"</...>_..."
			int ClosingElement = pos + Token.size();

			// check of other opening tags
			pos = MatchFirstOf(ElementsStr, { "<" + TagName }, uselessToken, ClosingTag);
			//"..._<..."
			int SimilarOpeningElement = pos;
			if (pos != -1)
				SimilarOpeningElement += Token.size();
			while (SimilarOpeningElement != -1 && SimilarOpeningElement < ClosingElement)
			{
				pos = MatchFirstOf(ElementsStr, { "</" + TagName + ">" }, Token, ClosingElement);
				ClosingElement = pos + Token.size();

				pos = MatchFirstOf(ElementsStr, { "<" + TagName }, uselessToken, SimilarOpeningElement);
				SimilarOpeningElement = pos;
				if (pos != -1)
					SimilarOpeningElement += Token.size();
			}

			i = ClosingElement;
			ReadAttributes(ElementsStr.substr(OpenTag, ClosingTag - OpenTag), element.Children.back());
			ReadElements(ElementsStr.substr(OpeningElement, ClosingElement - Token.size() - OpeningElement), element.Children.back());
		}
		// Has no attributes, has no children
		if (Token == "/>")
		{
			i = ClosingTag;
			ReadAttributes(ElementsStr.substr(OpenTag, ClosingTag - OpenTag), element.Children.back());
		}
	}
	return 0;
}

int XMLReader::ReadAttributes(string ElementStr, XML::Element & element)
{
	for (int i = 0; i < ElementStr.size(); i++)
	{
		int pos;
		string Token;
		pos = MatchFirstOf(ElementStr, { " ", ">", "/>" }, Token, i - 1);
		int AttributeNameStart = pos + Token.size();
		if (Token == " ")
		{
			pos = MatchFirstOf(ElementStr, { "=" }, Token, i);
			int AttributeNameEnd = pos;
			pos = MatchFirstOf(ElementStr, { "\"" }, Token, AttributeNameEnd);
			int AttributeValueStart = pos + Token.size();
			pos = MatchFirstOf(ElementStr, { "\"" }, Token, AttributeValueStart);
			int AttributeValueEnd = pos;

			i = AttributeValueEnd + Token.size();

			element.SetAttribute(ElementStr.substr(AttributeNameStart, AttributeNameEnd - AttributeNameStart),
				ElementStr.substr(AttributeValueStart, AttributeValueEnd - AttributeValueStart));
		}
	}
	return 0;
}
