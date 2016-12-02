#pragma once
#include <vector>
#include <functional>
#include "Maths.h"
#include "Text.h"
#include "ImageLoader.h"
using namespace std;
class UIElement
{
public:
	struct Element {
		Element() {}
		Element(string ID, int z_index = 1) { this->z_index = z_index; this->ID = ID; }
		int z_index;
		string ID;
		bool operator<(const UIElement::Element& rhs) const
		{
			if (this->z_index == rhs.z_index)
			{
				return this->ID < rhs.ID;
			}
			return this->z_index > rhs.z_index;
		}
	};
public:
	UIElement(string Name, string Filename, int z_index=1);
	~UIElement();
	void AddHoverEvent(std::function<void(UIElement*)> onhover);
	void AddHoverDoneEvent(std::function<void(UIElement*)> onhoverdone);
	void AddReturnDefaultEvent(std::function<void(UIElement*)> onreturndefault);
	void AddClickEvent(std::function<void(UIElement*)> onclick);
	UIElement* GetHover(vec2 MouseCoords);
	UIElement* GetClick(vec2 MouseCoords);
	void OnHover();
	void OnHoverDone();
	void OnReturnDefault();
	void OnClick();

	void AppendChild(UIElement*);
	void RemoveChild(UIElement*);
	void RemoveChild(string Name);
	void Draw();
	void SetByTrueSize(vec2 TopLeft);
	UIElement* GetUIElement(string Name);
	void ChangePicture(string Filename);
	vec2 TopLeft;
	vec2 BotRight;
	vec2 TextPosition;
	string innerText;
	vec2 TrueSize;
	
private:
	std::function<void(UIElement*)> hover;
	std::function<void(UIElement*)> hoverdone;
	std::function<void(UIElement*)> returndefault;
	std::function<void(UIElement*)> click;
	void UpdateParentSize(vec2 TopLeft, vec2 BotRight);
	void LoadPicture(string Filename);
	Element Name;
	int Width, Height;
	ImageLoader* UIImage;
	map<Element,UIElement*> Children;
	Text text;
	UIElement* Parent;
	bool IsRoot;
	static map <string, ImageLoader*> Repository;
};

