#include "UIElement.h"


UIElement::UIElement(string Name,string Filename)
{
	UIImage.LoadTexture(Filename);
	UIImage.LoadVAO();
	this->Name = Name;
}

UIElement::~UIElement()
{
}

void UIElement::AddHoverEvent(void(*func)())
{
	this->hover = func;
}

void UIElement::AddClickEvent(void(*func)())
{
	this->click = func;
}

void UIElement::OnHover()
{
	/*if ()
	hover();
	for (auto uie : Children)
	{
		uie.second->OnHover();
	}*/
}

void UIElement::OnClick()
{
	/*hover();
	for (auto uie : Children)
	{
		if ()
			uie.second->OnHover();
	}*/
}

void UIElement::AppendChild(UIElement * child)
{
	Children[child->Name] = child;
}

void UIElement::Draw(vec2 TopLeft, vec2 BotRight)
{
	this->TopLeft = TopLeft;
	this->BotRight = BotRight;
	for(auto uie : Children)
	{
		uie.second->Draw(uie.second->TopLeft, uie.second->BotRight);
	}
	this->Draw(TopLeft, BotRight);
}

void UIElement::GetUIElement(string Name)
{
}
