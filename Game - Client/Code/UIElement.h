#pragma once
#include <vector>
#include "ImageLoader.h"
using namespace std;
class UIElement
{
public:
	UIElement(string Name, string Filename);
	~UIElement();
	void AddHoverEvent(void(*func)());
	void AddClickEvent(void(*func)());
	void OnHover();
	void OnClick();
	void AppendChild(UIElement*);
	void Draw(vec2 TopLeft,vec2 BotRight);
	void GetUIElement(string Name);
	vec2 TopLeft;
	vec2 BotRight;
private:
	void(*hover)();
	void(*click)();
	string Name;
	int Width, Height;
	ImageLoader UIImage;
	map<string,UIElement*> Children;
};

