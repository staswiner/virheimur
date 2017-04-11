#include "UIElement.h"


bool SortElement(const UIElement::Element& lhs, const UIElement::Element& rhs)
{
	if (lhs.z_index == rhs.z_index)
	{
		return lhs.ID < rhs.ID;
	}
	return lhs.z_index < rhs.z_index;
}

map<string, ImageLoader*> UIElement::Repository;

UIElement::UIElement(string Name,string Filename,int z_index)
{
	if (Filename == "")
	{
		this->IsRoot = true;
	}
	else
	{
		this->IsRoot = false;
		this->LoadPicture(Filename);
		this->TrueSize = UIImage->GetTrueSize();
	}

	this->Name = Element(Name,z_index);
	this->Parent = nullptr;
}

UIElement::~UIElement()
{
}

void UIElement::AddHoverEvent(std::function<void(UIElement*)> onhover)
{
	this->hover = onhover;
}

void UIElement::AddHoverDoneEvent(std::function<void(UIElement*)> onhoverdone)
{
	this->hoverdone = onhoverdone;
}

void UIElement::AddReturnDefaultEvent(std::function<void(UIElement*)> onreturndefault)
{
	this->returndefault = onreturndefault;
}

void UIElement::AddClickEvent(std::function<void(UIElement*)> onclick)
{
	this->click = onclick;
}

void UIElement::AddPressEvent(std::function<void(UIElement*)> onpress)
{
	this->press = onpress;

}

void UIElement::AddTextChangedEvent(std::function<void(UIElement*)> ontextchanged)
{
	this->textchanged = ontextchanged;
}

UIElement* UIElement::GetHover(vec2 MouseCoords)
{
	for (auto uie : Children)
	{
		UIElement * focus;
		if (focus = uie.second->GetHover(MouseCoords))
		{
			return focus;
		}
	}
	if (Stas::Maths::IsIn(this->TopLeft, this->BotRight, MouseCoords))
	{
		return this;
	}
	return nullptr;
}

UIElement* UIElement::GetClick(vec2 MouseCoords)
{
	for (auto uie : Children)
	{
		UIElement * focus;
		if (focus = uie.second->GetClick(MouseCoords))
		{
			return focus;
		}
	}
	if (Stas::Maths::IsIn(this->TopLeft, this->BotRight, MouseCoords))
	{
		return this;
	}
	return nullptr;
	std::bind(&UIElement::Destroy, this);

}

void UIElement::OnHover()
{
	// checks if function bind to anything
	if (hover)
	{
		hover(this);
	}
}

void UIElement::OnHoverDone()
{
	// checks if function bind to anything
	if (hoverdone)
	{
		hoverdone(this);
	}
}

void UIElement::OnReturnDefault()
{
	if (returndefault)
		returndefault(this);
}

void UIElement::OnClick()
{
	// checks if function bind to anything
	if (click)
	{
		click(this);
	}
}

void UIElement::OnPress()
{
	// checks if function bind to anything
	if (press)
	{
		press(this);
	}
}

void UIElement::OnTextChanged()
{
	// checks if function bind to anything
	if (textchanged)
	{
		textchanged(this);
	}
}

void UIElement::Hide()
{
	for (auto& uie : Children)
	{
		uie.second->Hide();
	}
	this->visible = false;
}

void UIElement::Show()
{
	for (auto& uie : Children)
	{
		uie.second->Show();
	}
	this->visible = true;
}

void UIElement::Destroy()
{
	for (auto uie = this->Children.begin(); uie!= this->Children.end();uie++)
	{
		uie->second->Destroy();
	}
	delete this;
}

UIElement* UIElement::FocusNext()
{
	if (this->Children.size() > 0)
	{
		return this->Children.begin()->second;
	}
	else if ((++this->Parent->Children.find(this->Name)) != this->Parent->Children.end())
	{

		UIElement* brother = (++this->Parent->Children.find(this->Name))->second;
		return brother;
	}
	else
	{
		return Parent;
	}

}

void UIElement::AppendChild(UIElement * child)
{
	Children[child->Name] = child;
	child->Parent = this;
}

void UIElement::RemoveChild(UIElement * Element)
{
	for (auto uie : Element->Children)
	{
		RemoveChild(uie.second);
		Parent->Children.erase(this->Name);
		delete this;
	}
}

void UIElement::RemoveChild(string Name)
{
	//// check for this element
	//if (Name == this->Name.ID)
	//	return this;
	// Find element
	UIElement * RootDelete = nullptr;
	for (auto uie : Children)
	{
		if (uie.second->Name.ID == Name)
		{
			RootDelete = uie.second;
			break;
		}
	}
	// No Such Element
	if (!RootDelete)
		return;
	// check for children
	RemoveChild(RootDelete);
}

void UIElement::Draw()
{
	if (visible == false)
		return;
	// back to front, draws parent before child
	if (this->IsRoot == false)
	{
		float FontSize = (float)this->style.font.size;
		vec2 margin(20.0f,((BotRight.y-TopLeft.y) + FontSize/2.0f)/2.0f);
		TextPosition = TopLeft + margin;
		this->UIImage->Draw(this->TopLeft, this->BotRight);


		Text::LoadTextShader(vec3(0, 0, 0));
		Text& text = Text::getInstance();
		// Mask text
		string NewInnerText;
		if (this->style.MaskedText)
		{
			NewInnerText.resize(this->innerText.size(), '*');
		}
		else
		{
			NewInnerText = this->innerText;
		}
		text.RenderText(NewInnerText, this->TextPosition.x, this->TextPosition.y,
			(this->BotRight.x-this->TopLeft.x) - margin.x*2, FontSize, style.font.color);
	}
	// proceeds to drawing children
	for (auto uie : Children)
	{
		uie.second->Draw();
	}
}

void UIElement::SetByTrueSize(vec2 TopLeft)
{
	this->BotRight = TopLeft + TrueSize;
}

void UIElement::SetByTrueSize()
{
	this->BotRight = this->TopLeft + TrueSize;
}

UIElement* UIElement::GetUIElement(string Name)
{
	// check for this element
	if (Name == this->Name.ID)
		return this;
	// check for children
	for (auto uie : Children)
	{
		UIElement * element = uie.second->GetUIElement(Name);
		if (element != nullptr)
			return element;
	}
	// end of branch
	return nullptr;
}
void UIElement::ChangePicture(string Filename)
{
	this->LoadPicture(Filename);
	this->TrueSize = UIImage->GetTrueSize();
}
// this function only increases size, might be bad if sizes need to get back to normal
void UIElement::UpdateParentSize(vec2 TopLeft, vec2 BotRight)
{
	if (this->Parent != nullptr)
		this->Parent->UpdateParentSize(TopLeft, BotRight);
	// Left
	if (this->TopLeft.x > TopLeft.x)
		this->TopLeft.x = TopLeft.x;
	// Top
	if (this->TopLeft.y > TopLeft.y)
		this->TopLeft.y = TopLeft.y;	
	// Right
	if (this->BotRight.x < BotRight.x)
		this->BotRight.x = BotRight.x;
	// Bot
	if (this->BotRight.y < BotRight.y)
		this->BotRight.y = BotRight.y;
}

void UIElement::LoadPicture(string Filename)
{
	if (Repository.find(Filename) == Repository.end())
	{
		Repository[Filename] = new ImageLoader();
		Repository[Filename]->Initialize(Filename);
	}
	this->UIImage = Repository[Filename];
}
